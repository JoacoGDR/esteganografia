#include <stdio.h>
#include <stdlib.h>
#include "BMPImage.h"
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "./imageReconstruction.h" 
#include "./shadowGeneration.h" 



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
        exit(EXIT_FAILURE);
    }

    // Dynamically allocate memory for the file list
    char ** fileList = NULL;
    *n = 0;

    while ((entry = readdir(dir)) != NULL) {
        int len = strlen(folderPath) + strlen(entry->d_name) + 1;
        char *path= malloc(len);
        snprintf(path, len, "%s%s", folderPath, entry->d_name);
        struct stat fileStat;
        if (lstat(path, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {  // Check if the entry is a regular file
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
        free(path);
    }

    closedir(dir);

    return fileList;
}

BMPImage ** getParticipants(char ** filenames, int n){
    BMPImage ** participants = malloc(sizeof(BMPImage*)* (n));
    int width, height;
    for(int i = 0; i < n; i++){
        participants[i] = readBMP(filenames[i]);
        if(i > 0 && (width != participants[i]->width || height != participants[i]->height)){
            perror("All images must have the same width and height\n");
            exit(EXIT_FAILURE);
        }
        if(participants[i]->bitsPerPixel != 8){
            printf("Image must have 8 bits per pixel\n");
            exit(EXIT_FAILURE);
        }

        width = participants[i]->width;
        height = participants[i]->height;

        if (participants[i] == NULL) {
            perror("Failed to read the BMP image.\n");
            exit(EXIT_FAILURE);
        }
    }
    return participants;
}

int main(int argc, char* argv[]){
    srand(time(NULL));   // Initialization, should only be called once.
    if(argc != 5){
        perror("Wrong number of arguments. Example: \n./ss [d] [path secret image] [k] [path images directory]\n./ss [d] [path to save restored image] [k] [path images directory]\n");
        return 1;
    }
    char operation = argv[1][0];
    char * image = argv[2];
    int k = atoi(argv[3]);
    char* imagesDirectory = argv[4];
    int n;

    if(k < 3 || k > 8){
        perror("k must be between 3 and 8\n");
        exit(EXIT_FAILURE);
    }

    if(operation == 'd'){
        // Read the BMP image

        char ** filenames = getFiles(imagesDirectory, &n);
        if(n < k){
            perror("There must be at least k images in the directory\n");
            exit(EXIT_FAILURE);
        }
        BMPImage ** participants = getParticipants(filenames, n);

        const char * imageToHide = image;
        BMPImage* hiddenImage = readBMP(imageToHide);
        if (hiddenImage == NULL) {
            perror("Failed to read the BMP image.\n");
            exit(EXIT_FAILURE);
        }

        if(hiddenImage->bitsPerPixel != 8){
            perror("Image must have 8 bits per pixel\n");
            exit(EXIT_FAILURE);
        }
        
        if(hiddenImage->width != participants[0]->width || hiddenImage->height != participants[0]->height){
            perror("All images must have the same width and height\n");
            exit(EXIT_FAILURE);
        }

        Shadow * shadows = generateShadowsFromFile(hiddenImage, k, n);

        for(int i = 0; i < n; i++){
            hideShadowInImage(participants[i], shadows[i], k);
        }

    } else if(operation == 'r'){

        char ** filenames = getFiles(imagesDirectory, &n);
        if(n < k){
            perror("There must be at least k images in the directory\n");
            exit(EXIT_FAILURE);
        }
        BMPImage ** participants = getParticipants(filenames, k);

        reconstructImage(image, participants, k);
    } else {
        perror("Invalid operation: must be \'d\' to distribute the secret or \'r\' to recover it\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}