#include <stdio.h>
#include "modularOperations.c"
#include "BMPImage.c"
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct ImageBlock {
    int blockNumber;
    int * f;
    int * g;
} typedef ImageBlock;

struct Shadow {
    int shadowNumber;
    char * data; // v0,sn || v1,sn || v2,sn ...
} typedef Shadow;



char ** divideString(char* data, int datalength,  int blockSize){

    int blocks = datalength/blockSize;
    char ** strings = malloc(blocks* sizeof(char*));
    char dest;   
    for (size_t i = 0; i < blocks; i++)
    {
        strings[i] = malloc((blockSize+1) * sizeof(char));
        strncpy(strings[i], data , blockSize);
        data+=blockSize;
        strings[i][blockSize] = '\0';
    }
    return strings;
}


 
//a:[012..k-1]   b:[k...2k-2-1]
ImageBlock * decomposeImage(BMPImage * image, int k){

    int r = rand() %251;

    int imageSize = image->bitsPerPixel * image->width * image->height;
    char * imageBytes = image->data;
    int blockSize = (2*k) - 2;
    char ** blocks = divideString(imageBytes, imageSize, blockSize);

    int t = imageSize/blockSize;

    ImageBlock * imageBlocks = malloc(t * sizeof(ImageBlock));

    for (size_t i = 0; i < t; i++)
    {
        imageBlocks[i].blockNumber = i;
        imageBlocks[i].f = malloc(k * sizeof(int));
        imageBlocks[i].g = malloc(k * sizeof(int));

        for (size_t j = 0; j < blockSize; j++)
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
        
        imageBlocks[i].g[0] = (-r1 * a0 - a1) % 251 ;
        imageBlocks[i].g[1] = (-r2 * a0 - a1) % 251;

    }

    return imageBlocks;
}


int main(int argc, char const *argv[])
{



    const char* filename = "mujer.bmp";  // Replace with your BMP file path    
    // Read the BMP image
    BMPImage* image = readBMP(filename);
    if (image == NULL) {
        printf("Failed to read the BMP image.\n");
        return 1;
    }


    srand(time(NULL));   // Initialization, should only be called once.
    printf("bitsPerPixel: %d\n", image->bitsPerPixel);
    printf("width: %d\n", image->width);
    printf("height: %d\n", image->height);

    int imageSize = image->bitsPerPixel * image->width * image->height;
    printf("imageSize: %d\n", imageSize);
    int k = 3;
    int n = 5;
    int t = imageSize/(2*k-2);
    printf("t: %d\n", t);
    ImageBlock * imageBlocks = decomposeImage(image, k);
    
    for (size_t i = 0; i < 20; i++)
    {
        printf("Block %d\n", imageBlocks[i].blockNumber);
        printf("f: ");
        for (size_t j = 0; j < k; j++)
        {
            printf("%d ", imageBlocks[i].f[j]);
        }
        printf("\n");
        printf("g: ");
        for (size_t j = 0; j < k; j++)
        {
            printf("%d ", imageBlocks[i].g[j]);
        }
        printf("\n");
    }

    
    return 0;
}