#ifndef IMAGE_RECONSTRUCTION_H
#define IMAGE_RECONSTRUCTION_H

#include "shadowStructures.h"

int extractLSB4(unsigned char * img);

int extractLSB2(unsigned char * img);


Shadow extractShadowFromImage(BMPImage * img,  int k);


ImageBlock * reconstructBlocks(Shadow * shadows, int k);

unsigned char * buildImageFromBlocks(ImageBlock * blocks, int t, int k);


//BMPImage * reconstructImage(char * reconstructdImage, BMPImage ** images, int k);
void reconstructImage(char * reconstructdImage, BMPImage ** images, int k);



#endif