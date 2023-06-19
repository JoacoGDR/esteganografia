#include <stdio.h>
#include <stdlib.h>
#include "imageReconstruction.h" 
#include "shadowGeneration.h" 
#include "BMPImage.h"
#include <time.h>
#include <string.h>
#include <dirent.h>

void prependString(char* original, const char* prepend) {
    char temp[strlen(original) + 1];  // Create a temporary string to hold the original value
    strcpy(temp, original);  // Copy the original string to the temporary string
    strcpy(original, prepend);  // Copy the prepend string to the original string
    strcat(original, temp);  // Concatenate the temporary string (original value) to the original string
}

char ** getFiles(const char * folderPath, int * n){
    DIR *dir;
    struct dirent *entry;

    dir = opendir(folderPath);
    if (dir == NULL) {
        perror("Unable to open directory");
        *n = 0;
        return NULL;
    }

    // Dynamically allocate memory for the file list
    char ** fileList = NULL;
    *n = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Check if the entry is a regular file
            // Increase the file count and reallocate memory for the updated file list
            const char *extension = strrchr(entry->d_name, '.');
            if (extension == NULL || strcmp(extension, ".bmp") != 0) {
                // return error
                perror("The file isn't in .bmp format");
                exit(EXIT_FAILURE);

            }
            (*n)++;
            fileList = realloc(fileList, (*n) * sizeof(char*));
            fileList[*n - 1] = malloc((strlen(entry->d_name) + strlen(folderPath) + 1) * sizeof(char));
            strcpy(fileList[*n - 1], entry->d_name);
            prependString(fileList[*n - 1], folderPath);
        }
    }

    closedir(dir);

    return fileList;
}

//main.o operacion imagen.bmp k carpeta_de_imagenes
int main(int argc, char* argv[]){
    srand(time(NULL));   // Initialization, should only be called once.
    if(argc != 5){
        printf("Error: numero de argumentos invalido\n");
        return 1;
    }
    char operation = argv[1][0];
    char* image = argv[2];
    int k = atoi(argv[3]);
    char* imagesDirectory = argv[4];

    int n;
    char ** filenames = getFiles(imagesDirectory, &n);
    // int n=3;
    // char * filenames[3] = {"../images/Albertshare.bmp", "../images/Carlitosshare.bmp", "../images/Johnshare.bmp"};

    BMPImage ** participants = malloc(sizeof(BMPImage*)* (n));
    int width, height;
    for(int i = 0; i < n; i++){
        participants[i] = readBMP(filenames[i]);
        if(i > 0 && (width != participants[i]->width || height != participants[i]->height)){
            printf("Error: las imagenes deben tener el mismo tamaño\n");
            return 1;
        }
        if(participants[i]->bitsPerPixel != 8){
            printf("Error: las imagenes deben tener 8 bits por pixel\n");
            return 1;
        }

        width = participants[i]->width;
        height = participants[i]->height;

        if (participants[i] == NULL) {
            
            printf("Failed to read the BMP image.\n");
            return 1;
        }
    }

    if(operation == 'd'){
        // Read the BMP image
        const char * imageToHide = image;
        BMPImage* hiddenImage = readBMP(imageToHide);
        if (hiddenImage == NULL) {
            printf("Failed to read the BMP image.\n");
            return 1;
        }

        Shadow * shadows = generateShadowsFromFile(hiddenImage, k, n);

        for(int i = 0; i < n; i++){
            hideShadowInImage(participants[i], shadows[i], k);
        }
    } else if(operation == 'r'){

        //BMPImage * reconstructedImage = reconstructImage(image, participants, k);
        reconstructImage(image, participants, k);
    } else {

        printf("Error: operacion invalida. Debería ser: \'d\' para esconder la file o \'r\' para recuperarla\n");
        return 1;
        // print error and do nothing
    }

    //printf("HIDDEN\n----------------\n");
    //printImageData(hiddenImage);

    // Shadow * shadows = generateShadowsFromFile(hiddenImage, k, n);

    // for(int i = 0; i < n; i++){
    //     hideShadowInImage(participants[i], shadows[i], k);
    // }
    
    //printf("\n-------------------\nRECONSTRUCTED\n----------------\n");
    // BMPImage * reconstructedImage = reconstructImage(participants, k);
    //printImageData(reconstructedImage);
    return 0;
}