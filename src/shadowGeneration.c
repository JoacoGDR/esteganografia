#include <stdio.h>
#include "modularOperations.c"
#include "BMPImage.c"
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct ImageBlock {
    int blockNumber;
    size_t * f;
    size_t * g;
} typedef ImageBlock;

struct Shadow {
    size_t shadowNumber;
    int t;
    V * shadow; // v0,sn || v1,sn || v2,sn ...
} typedef Shadow;

struct V {
    size_t m; //f evaluado
    size_t d; //g evaluado
} typedef V;

//"123141562"
unsigned char ** divideBytes(unsigned char* data, int datalength,  int blockSize){

    int blocks = datalength/blockSize;
    unsigned char ** bytes = malloc(blocks* sizeof(unsigned char*));
    for (size_t i = 0; i < blocks; i++)
    {
        bytes[i] = malloc((blockSize) * sizeof(unsigned char));
        memcpy(bytes[i], data , blockSize);
        data+=blockSize;
    }
    return bytes;
}

int evaluate(size_t * f, size_t x){
    size_t result = 0;
    for (size_t i = 0; i < 2; i++)
    {
        result += f[i] * pow(x, i);
        result = result % 251;
    }
    return result % 251;
}

Shadow * generateShadows(ImageBlock * blocks,int t, int n){
    Shadow * shadows = malloc(n * sizeof(Shadow));
    for(int i =0; i<n; i++){
        shadows[i].shadow = malloc(t * sizeof(V));
        shadows[i].shadowNumber = i;
        for (size_t j = 0; j < t; j++){
            shadows[i].shadow[j].m = evaluate(blocks[j].f, i);
            shadows[i].shadow[j].d = evaluate(blocks[j].g, i);
        }
        return shadows;
    }
}

//a:[012..k-1]   b:[k...2k-2-1]
ImageBlock * decomposeImage(BMPImage * image, int k){

    int r = rand() %251;

    int imageSize = image->bitsPerPixel * image->width * image->height;
    imageSize = imageSize > 0 ? imageSize: imageSize * -1;
    unsigned char * imageBytes = image->data;
    int blockSize = (2*k) - 2;
    unsigned char ** blocks = divideBytes(imageBytes, imageSize, blockSize);

    int t = imageSize/blockSize;

    ImageBlock * imageBlocks = malloc(t * sizeof(ImageBlock));

    for (int i = 0; i < t; i++)
    {
        imageBlocks[i].blockNumber = i;
        imageBlocks[i].f = malloc(k * sizeof(int));
        imageBlocks[i].g = malloc(k * sizeof(int));

        for (int j = 0; j < blockSize; j++)
        {
            //b0 y b1 tienen que ser generados
            if(j < k){
                imageBlocks[i].f[j] = blocks[i][j];
            }else{
                imageBlocks[i].g[j-k+2] = blocks[i][j];
            }
        }

        int a0 = imageBlocks[i].f[0] == 0 ? 1: imageBlocks[i].f[0];
        int a1 = imageBlocks[i].f[1] == 0 ? 1: imageBlocks[i].f[1];

        int r1 = rand() %251;
        int r2 = rand() %251;
        
        imageBlocks[i].g[0] = (-r1 * a0 - a1) % 251;
        imageBlocks[i].g[0] = imageBlocks[i].g[0] < 0? imageBlocks[i].g[0] + 251: imageBlocks[i].g[0];

        imageBlocks[i].g[1] = (-r2 * a0 - a1) % 251;
        imageBlocks[i].g[1] = imageBlocks[i].g[1] < 0? imageBlocks[i].g[1] + 251: imageBlocks[i].g[1];

    }

    return imageBlocks;
}

Shadow * generateShadowsFromFile(char * filename, int k, int n){

    BMPImage* image = readBMP(filename);
    if (image == NULL) {
        printf("Failed to read the BMP image.\n");
        return 1;
    }

    int imageSize = image->bitsPerPixel * image->width * image->height;
    imageSize = imageSize > 0 ? imageSize: imageSize * -1;
    int t = imageSize/(2*k-2);

    ImageBlock * imageBlocks = decomposeImage(image, k);
    return generateShadows(imageBlocks, t, n);
}

void stepBitsLSB2(unsigned char * byte, unsigned char X){
    unsigned char maskA = 0x03; // 00000011
    unsigned char maskB = maskA << 2; // 00001100
    unsigned char maskC = maskB << 2; // 00110000
    unsigned char maskD = maskC << 2; // 11000000

    unsigned char bitsA = (X & maskD) >> 6; 
    unsigned char bitsB = (X & maskC) >> 4;
    unsigned char bitsC = (X & maskB) >> 2;
    unsigned char bitsD = X & maskA;
    
    unsigned char * A = byte;
    unsigned char * B = byte+1;
    unsigned char * C = byte+2;
    unsigned char * D = byte+3;

    *A = (*A & ~maskA) | bitsA;
    *B = (*B & ~maskA) | bitsB;
    *C = (*C & ~maskA) | bitsC;
    *D = (*D & ~maskA) | bitsD;
}


void stepBitsLSB4(unsigned char * byte, unsigned char X) {
    unsigned char mask = 0x0F;  // Mask to extract the 4 least significant bits

    // Extract the first 4 bits of X
    unsigned char * A = byte;
    unsigned char * B = byte+1;
    
    unsigned char firstBits = X & ~mask;
    firstBits = firstBits >> 4;
    
    unsigned char lastBits = X & mask;

    // Step the least significant bits of A and B with the extracted bits
    *A = (*A & ~mask) | firstBits;
    *B = (*B & ~mask) | lastBits;
}


unsigned char * lsbHide(BMPImage * img, Shadow shadow, int k){
    unsigned char * image = img->data;
    img->fileHeader.bfReserved1 = shadow.shadowNumber;
    V * vs = shadow.shadow;
    int t = shadow.t;
    if(k < 5) {
        for(int i = 0; i < t; i++){
            stepBitsLSB4(image, vs[i].m);
            image = image+2;
            stepBitsLSB4(image, vs[i].d);
            image = image+2;
        }
    } else {
        for(int i = 0; i < t; i++){
            stepBitsLSB2(image, vs[i].m);
            image = image+4;
            stepBitsLSB2(image, vs[i].d);
            image = image+4;
        }
    }
}



// int main(int argc, char const *argv[])
// {
//     const char* filename = "blanco4x4.bmp";  // Replace with your BMP file path    
//     // Read the BMP image
//     BMPImage* image = readBMP(filename);
//     if (image == NULL) {
//         printf("Failed to read the BMP image.\n");
//         return 1;
//     }


//     srand(time(NULL));   // Initialization, should only be called once.

//     printf("bitsPerPixel: %d\n", image->bitsPerPixel);
//     printf("width: %d\n", image->width);
//     printf("height: %d\n", image->height);

//     int imageSize = image->bitsPerPixel * image->width * image->height;
//     imageSize = imageSize > 0 ? imageSize: imageSize * -1;
//     printf("imageSize: %d\n", imageSize);

//     int k = 3;
//     int n = 10;
//     int t = imageSize/(2*k-2);

//     printf("t: %d\n", t);
//     ImageBlock * imageBlocks = decomposeImage(image, k);
//     V ** vs = generateVs(imageBlocks, t, n);

//     return 0;
// }