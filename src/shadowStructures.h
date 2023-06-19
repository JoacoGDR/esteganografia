#ifndef SHADOWSTRUCTURES_H
#define SHADOWSTRUCTURES_H

#include "BMPImage.h"


typedef struct ImageBlock {
    int blockNumber;
    int * f;
    int * g;
} ImageBlock;

typedef struct V {
    int m; //f evaluado
    int d; //g evaluado
} V;

typedef struct Shadow {
    int shadowNumber;
    int t;
    V * shadow; // v0,sn || v1,sn || v2,sn ...
} Shadow;

#endif


