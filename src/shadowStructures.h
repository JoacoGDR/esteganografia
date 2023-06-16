#ifndef SHADOWSTRUCTURES_H
#define SHADOWSTRUCTURES_H

#include "BMPImage.h"


struct ImageBlock {
    int blockNumber;
    int * f;
    int * g;
} typedef ImageBlock;

struct V {
    int m; //f evaluado
    int d; //g evaluado
} typedef V;

struct Shadow {
    int shadowNumber;
    int t;
    V * shadow; // v0,sn || v1,sn || v2,sn ...
} typedef Shadow;

#endif


