#ifndef GAUSS_H
#define GAUSS_H
#include <stdio.h>
#include <stdlib.h>

#define MOD 251

typedef struct {
    int x;
    int y;
} Point;

int mod(int n);

int modInverse(int n);

void polynomialCoefficients(Point* points, int numPoints, int * coefficients, int degree);


int check(Point p, int * coefficients, int degree);

#endif
