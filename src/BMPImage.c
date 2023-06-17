#include <stdio.h>
#include <stdlib.h>
#include "BMPImage.h"


BMPImage * createBMP(char * filename, int width, int height, int bitsPerPixel, unsigned char*data, unsigned char shadowNumber) {
  BMPImage *image = malloc(sizeof(BMPImage));
  image->width = width;
  image->height = height;
  image->bitsPerPixel = bitsPerPixel;
  image->data = data;
  image->filename = filename;
  image->shadowNumber = shadowNumber;

  return image;
}



void createBMPFile(BMPImage *image) {
  // Open the file.
  FILE* file = fopen(image->filename,"wb");
  if (file == NULL) {
    printf("Could not open file.\n");
    return;
  }
  
  // Write the file header.
  BITMAPFILEHEADER fileHeader;
  fileHeader.bfType = 0x4D42;
  fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + image->width * image->height * image->bitsPerPixel / 8;
  fileHeader.bfReserved1 = image->shadowNumber;
  fileHeader.bfReserved2 = 0;
  fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
  fwrite(&fileHeader, sizeof(fileHeader), 1, file);
  
  // Write the info header.
  BITMAPINFOHEADER infoHeader;
  infoHeader.biSize = sizeof(BITMAPINFOHEADER);
  infoHeader.biWidth = image->width;
  infoHeader.biHeight = image->height;
  infoHeader.biPlanes = 1;
  infoHeader.biBitCount = image->bitsPerPixel;
  infoHeader.biCompression = 0;
  infoHeader.biSizeImage = image->width * image->height * image->bitsPerPixel / 8;
  infoHeader.biXPelsPerMeter = 0;
  infoHeader.biYPelsPerMeter = 0;
  infoHeader.biClrUsed = 0;
  infoHeader.biClrImportant = 0;
  fwrite(&infoHeader, sizeof(infoHeader), 1, file);
  
  // Write the image data.
  fwrite(image->data, image->width * image->height * image->bitsPerPixel / 8, 1, file);
  
  // Close the file.
  fclose(file);
}

BMPImage *readBMP(const char* filename) {
  // Open the file.
  FILE* file = fopen(filename,"rb");
  if (file == NULL) {
    printf("Could not open file.\n");
    return NULL;
  }
  
  // Read the file header.
  BITMAPFILEHEADER fileHeader;
  fread(&fileHeader, sizeof(fileHeader), 1, file);
  if (fileHeader.bfType != 0x4D42) {
    // Not a valid BMP file.
    printf("Not a valid BMP file.\n");
    fclose(file);
    return NULL;
  }
  
  // Read the info header.
  BITMAPINFOHEADER infoHeader;
  fread(&infoHeader, sizeof(infoHeader), 1, file);
  
  // Read the image data.
  
  unsigned char* data = malloc(infoHeader.biSizeImage); 
  fread(data, infoHeader.biSizeImage, 1, file);
  fclose(file);
  
  // Create the image structure.
  BMPImage *image = malloc(sizeof(BMPImage));
  image->width = infoHeader.biWidth;
  image->height = infoHeader.biHeight;
  image->bitsPerPixel = infoHeader.biBitCount;
  image->data = data;
  image->filename = filename;
  image->shadowNumber = fileHeader.bfReserved1;
  
  return image;
}


void printImageData(BMPImage * img){
  int imagePixels = img->width * img->height;
  for(int i = 0; i < imagePixels; i++){
    printf("%hhu-", img->data[i]);
  }
  printf("\n");
}


int testBMPImage() {
 

  unsigned char * data = malloc(16);
  for(int i = 0; i < 16; i++){
    if(i % 7 == 0){
      data[i] = 128;
    } else {
      data[i] = 0;
    }
  }


  
  BMPImage *image2 = createBMP("imagencreada.bmp",4, 4, 8, data, 0);
  createBMPFile(image2);
  free(data);
  free(image2);

  // const char* filename = "mujer.bmp";  // Replace with your BMP file path
  
  // // Read the BMP image
  // BMPImage* image = readBMP(filename);
  // if (image == NULL) {
  //   printf("Failed to read the BMP image.\n");
  //   return 1;
  // }
  
  // // Print the image properties
  // printf("Image Properties:\n");
  // printf("Width: %d pixels\n", image->width);
  // printf("Height: %d pixels\n", image->height);
  // printf("Bits Per Pixel: %d\n", image->bitsPerPixel);
  // int imageSize = image->width * image->height;

  // for(int i = 0; i < imageSize; i++)
  //   printf("%d-", image->data[i]);
  
  // printf("imageSize: %d\n", imageSize);
  // // Cleanup
  // free(image->data);
  // free(image);

  return 0;
}



