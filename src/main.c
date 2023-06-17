#include <stdio.h>
#include <stdlib.h>
#include "imageReconstruction.h" 
#include "shadowGeneration.h" 
#include "BMPImage.h"
#include <time.h>

//main.o operacion imagen.bmp k carpeta_de_imagenes
int main(int argc, char* argv[]){
    srand(time(NULL));   // Initialization, should only be called once.
    if(argc != 5){
        printf("Error: numero de argumentos invalido\n");
        return 1;
    }
    char* operation = argv[1];
    char* image = argv[2];
    int k = atoi(argv[3]);
    char* imagesDirectory = argv[4];

    printf("operacion: %s\n", operation);
    printf("imagen: %s\n", image);
    printf("k: %d\n", k);
    printf("carpeta: %s\n", imagesDirectory);


    int n = 3;
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


    testBMPImage();
    
    return 0;
}