#ifndef SHADOW_GENERATION_H
#define SHADOW_GENERATION_H

#include "shadowStructures.h"

unsigned char ** divideBytes(unsigned char* data, int datalength,  int blockSize);

int evaluate(int * f, int x, int n);

Shadow * generateShadows(ImageBlock * blocks,int t, int n, int k);

ImageBlock * decomposeImage(BMPImage * image, int k);

Shadow * generateShadowsFromFile(BMPImage * image, int k, int n);

void stepBitsLSB2(unsigned char * byte, unsigned char X);

void stepBitsLSB4(unsigned char * byte, unsigned char X);

void printShadow(Shadow shadow);

void hideShadowInImage(BMPImage * img, Shadow shadow, int k);

int shadowsAreEqual(Shadow * s1, Shadow * s2);

int test(int argc, char const *argv[]);

#endif