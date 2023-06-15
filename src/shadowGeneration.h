#include <stdio.h>
#include "modularOperations.c"
#include "BMPImage.c"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

struct ImageBlock {
    int blockNumber;
    size_t * f;
    size_t * g;
} typedef ImageBlock;

struct V {
    size_t m; //f evaluado
    size_t d; //g evaluado
} typedef V;


struct Shadow {
    size_t shadowNumber;
    int t;
    V * shadow; // v0,sn || v1,sn || v2,sn ...
} typedef Shadow;