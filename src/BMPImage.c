#include <stdio.h>
#include <stdlib.h>

//Sources:
//https://en.wikipedia.org/wiki/BMP_file_format
//https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
#pragma pack(push, 1)
typedef struct {
  unsigned short bfType; //the characters "BM"
  unsigned int bfSize; //the size of the file in bytes
  unsigned short bfReserved1; // Shadow number
  unsigned short bfReserved2; //unused 
  unsigned int bfOffBits; //the offset of the pixel data inside the BMP file
} BITMAPFILEHEADER;

typedef struct {
  //https://en.wikipedia.org/wiki/BMP_file_format
  unsigned int biSize; //the size of this header, in bytes (40)
  int biWidth; //the bitmap width in pixels (signed integer)
  int biHeight; //the bitmap height in pixels (signed integer)
  unsigned short biPlanes; //the number of color planes (must be 1)
  unsigned short biBitCount; //the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32.
  unsigned int biCompression; //the compression method being used.
  unsigned int biSizeImage; //the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.
  int biXPelsPerMeter; //the horizontal resolution of the image. (pixel per meter, signed integer)
  int biYPelsPerMeter; //the vertical resolution of the image. (pixel per meter, signed integer)
  unsigned int biClrUsed; //the number of colors in the color palette, or 0 to default to 2n
  unsigned int biClrImportant; //the number of important colors used, or 0 when every color is important; generally ignored
} BITMAPINFOHEADER; 
#pragma pack(pop)

struct BMPImage {
  int width;
  int height;
  int bitsPerPixel;
  unsigned char *data;
  BITMAPFILEHEADER fileHeader;
} typedef BMPImage;

//TODO
//BMPImage *writeBMP(const recibe la tira de pixeles) {
  //escribir el header y después la tira de píxeles que recibe
//}

BMPImage *createBMP(int width, int height, int bitsPerPixel, unsigned char*data) {
  BMPImage *image = malloc(sizeof(BMPImage));
  image->width = width;
  image->height = height;
  image->bitsPerPixel = bitsPerPixel;
  image->data = data;
  return image;
}

void createBMPFile(BMPImage *image, const char* filename) {
  // Open the file.
  FILE* file = fopen(filename,"wb");
  if (file == NULL) {
    printf("Could not open file.\n");
    return;
  }
  
  // Write the file header.
  BITMAPFILEHEADER fileHeader;
  fileHeader.bfType = 0x4D42;
  fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + image->width * image->height * image->bitsPerPixel / 8;
  fileHeader.bfReserved1 = 0;
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
  image->fileHeader = fileHeader;
  
  return image;
}


void printImageData(BMPImage * img){
  int imagePixels = img->width * img->height * img->bitsPerPixel;
  for(int i = 0; i < imagePixels; i++){
    printf("%zu-", img->data[i]);
  }
  printf("\n");
}


// int main() {
 

//   unsigned char * data = malloc(16);
//   for(int i = 0; i < 16; i++){
//     if(i % 7 == 0){
//       data[i] = 128;
//     } else {
//       data[i] = 0;
//     }
//   }


  
//   BMPImage *image2 = createBMP(4, 4, 8, data);
//   createBMPFile(image2, "imagencreada.bmp");
//   free(data);
//   free(image2);

//   const char* filename = "mujer.bmp";  // Replace with your BMP file path
  
//   // Read the BMP image
//   BMPImage* image = readBMP(filename);
//   if (image == NULL) {
//     printf("Failed to read the BMP image.\n");
//     return 1;
//   }
  
//   // Print the image properties
//   printf("Image Properties:\n");
//   printf("Width: %d pixels\n", image->width);
//   printf("Height: %d pixels\n", image->height);
//   printf("Bits Per Pixel: %d\n", image->bitsPerPixel);
//   int imageSize = image->width * image->height;

//   for(int i = 0; i < imageSize; i++)
//     printf("%d-", image->data[i]);
  
//   printf("imageSize: %d\n", imageSize);
//   // Cleanup
//   free(image->data);
//   free(image);

//   return 0;
// }



