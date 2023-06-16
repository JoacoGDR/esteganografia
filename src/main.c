#include <stdio.h>
#include <stdlib.h>
#include "imageReconstruction.h" 
#include "shadowGeneration.h" 
#include <time.h>

int main(void){
    srand(time(NULL));   // Initialization, should only be called once.

    int n = 3, k=3;
    const char * imageToHide = "../images/negro4x4_2.bmp";
    const char * filenames[3] = {"../images/negro4x4.bmp", "../images/blanco4x4.bmp", "../images/test4x4.bmp"}; 
    
    // Read the BMP image
    BMPImage* hiddenImage = readBMP(imageToHide);
    if (hiddenImage == NULL) {
        printf("Failed to read the BMP image.\n");
        return 1;
    }

    BMPImage ** participants = malloc(sizeof(BMPImage*)*n);

    for(int i = 0; i < n; i++){
        participants[i] = readBMP(filenames[i]);
        if (participants[i] == NULL) {
            printf("Failed to read the BMP image.\n");
            return 1;
        }
    }

    
    Shadow * shadows = generateShadowsFromFile(hiddenImage, k, n);

    for(int i = 0; i < n; i++){
        hideShadowInImage(participants[i], shadows[i], k);
    }

    //empezar a recuperar
    BMPImage * reconstructedImage = reconstructImage(participants, k);

    printf("HIDDEN\n");
    printImageData(hiddenImage);
    printf("NEW\n");
    printImageData(reconstructedImage);
    
    return 0;
}