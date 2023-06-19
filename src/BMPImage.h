#ifndef BMPIMAGE_H
#define BMPIMAGE_H

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


typedef struct BMPImage {
  int width;
  int height;
  int bitsPerPixel;
  unsigned char *data;
  char * filename;
  unsigned char *metadata;
  unsigned char shadowNumber;
  BITMAPINFOHEADER infoHeader;
  BITMAPFILEHEADER fileHeader;
} BMPImage;

void createBMPFile(BMPImage *image);
BMPImage *readBMP(const char* filename);
void printImageData(BMPImage * img);
int testBMPImage();

#endif /* BMPIMAGE_H */
