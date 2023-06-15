#include "./imageReconstruction.h"

size_t extractLSB4(unsigned char * img){
    unsigned char mask = 0x0F;  // Mask to extract the 4 least significant bits
    unsigned char * A = img;
    unsigned char * B = img + 1;
    unsigned char firstBits = *A & mask; 
    unsigned char lastBits = *B & mask;  
    return (firstBits << 4) | lastBits;
}

size_t extractLSB2(unsigned char * img){
    unsigned char mask = 0x03; // 00000011

    unsigned char * A = img;
    unsigned char * B = img+1;
    unsigned char * C = img+2;
    unsigned char * D = img+3;

    unsigned char bitsA = *A & mask;
    unsigned char bitsB = *B & mask;
    unsigned char bitsC = *C & mask;
    unsigned char bitsD = *D & mask;

    return (bitsA << 6) | (bitsB << 4) | (bitsC << 2) | bitsD;
}


Shadow * extractShadowFromImage(BMPImage * img,  int k){
    unsigned char * image = img->data;
    Shadow * shadow = malloc(sizeof(Shadow));
    shadow->shadowNumber = img->fileHeader.bfReserved1;
    int t = (img->bitsPerPixel * img->width * img->height)/(2*k-2);
    shadow->t = t;
    shadow->shadow = malloc(t * sizeof(V));
    for(int i = 0; i < t; i++){
        if(k < 5) {
            shadow->shadow[i].m = extractLSB4(image);
            image = image+2;
            shadow->shadow[i].d = extractLSB4(image);
            image = image+2;
        } else {
            shadow->shadow[i].m = extractLSB2(image);
            image = image+4;
            shadow->shadow[i].d = extractLSB2(image);
            image = image+4;
        }
    }

    return shadow;
}




ImageBlock * reconstructBlocks(Shadow * shadows, int k){
    int t = shadows[0].t;
    ImageBlock * blocks = malloc(t * sizeof(ImageBlock));
    for(int i = 0; i < t; i++){
        blocks[i].f = malloc(k * sizeof(size_t));
        blocks[i].g = malloc(k * sizeof(size_t));
        
        for(int j = 0; j < k; j++){
            blocks[i].f[j] = shadows[j].shadow[i].m;
            blocks[i].g[j] = shadows[j].shadow[i].d;
            
        }

        

        // [(0,m1)(1,m2),..]
        // lagrange de esto para obtener f
        
        
    }
}

f(x) = a0 + a1*x + a2*x^2 + ... + ak*x^k 
Existe x tal que f(x) = ai para todo ai?


sum (mj * prod(x-xi, con i≠j)/prod(j-xi, con i≠j))
m0 (x-x1)(x-x2)...(x-xk-1)/(0-x1)...(0-xk-1) + ... + mk-1...


(x-x1)(x-x2) = x^2 - (x1+x2)x + x1*x2
(x-x1)(x-x2)(x-x3) = x^3 - (x1+x2+x3)x^2 + (x1*x2 + x1*x3 + x2*x3)x - x1*x2*x

()+x1()
ec = dsadsadsada


xk-1 por cada termino


void lagrange(ImageBlock * blocks, int t, int k){



    for(int i = 0; i < t; i++){

        for(int j = 0; j < k; j++){

            f[j] = blocks[i].f[j];

            g[j] = blocks[i].g[j];

        }

        //...
        //deberiamos tener ya f y g para el bloque i
        s*(x-1b)/(ia-ib) * )
        m0*(x-1)/(0-1) * ... * (x-j)/(0-j)

        [(0,m0), (1,m1), .., (j,mj),..., (k-1,mk-1))]

        f = [f0, f1, f2,..] // f(x) = f0 + f1*x + f2*x^2.. = [m0*(x-1)..*(x-k-1)]/[(0-1)*...*(0-k-1)] + ...

        polinomio(x)= [m0*(x-1)..*(x-k-1)]/[(0-1)*...*(0-k-1)] + ...
        
        s[1]*(x-s[0])/(i[0]-s[0]) 
        

        // lagrange de esto para obtener f
    }
}

BMPImage * reconstructImage(BMPImage ** images){

}





for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            prod = 1.0;
            for (j = 0; j < n; j++) {
                if (j != i) {
                    prod *= (points[k].x - points[j].x) / (points[i].x - points[j].x);
                }
            }
            coefficients[k] += prod*coeff[i];
        }
    }


s (x-x1)(x-x2)(1-x1)(1-x2)



coef= [2,3,4]
coefficients = [0,0,0]
(1,2)(2,3)(3,4)

k=0
    i=0
        prod = 1
        j=0 no entra i=j
        j=1 => prod *= (1-2)/(1-2) = 1
        j=2 => prod *= (1-3)/(1-3) = 1


        coefficients[0] += 1*coef[0] = 2
    i=1
        prod = 1
        j=0 => prod *= (1-1)/(2-1) = 0
        j=1 no entra i=j
        j=2 => prod *= (1-3)/(2-3) = 1
        coefficients[0] += 0*coef[1] = 2
    i=2
        prod = 1
        j=0 => prod *= (1-1)/(3-1) = 0
        j=1 => prod *= (1-2)/(3-2) = 0
        j=2 no entra i=j
        coefficients[0] += 0*coef[2] = 2
k=1  //(1,2)(2,3)(3,4)
    i=0
        prod = 1
        j=0 no entra i=j
        j=1 => prod *= (2-2)/(1-2) = 0
        j=2 => prod *= (2-3)/(1-3) = 0
        coefficients[1] += 0*coef[0] = 0
    i=1
        prod = 1
        j=0 => prod *= (2-1)/(2-1) = 1
        j=1 no entra i=j
        j=2 => prod *= (2-3)/(2-3) = 1
        coefficients[1] += 1*coef[1] = 3
    i=2
        prod = 1
        j=0 => prod *= (2-1)/(3-1) = 1/2
        j=1 => prod *= (2-2)/(3-2) = 0
        j=2 no entra i=j
        coefficients[1] += 0*coef[2] = 3
k=2 //(1,2)(2,3)(3,4)
    i=0
        prod = 1
        j=0 no entra i=j
        j=1 => prod *= (3-2)/(1-2) = -1
        j=2 => prod *= (3-3)/(1-3) = 0
        coefficients[2] += 0*coef[0] = 0
    i=1
        prod = 1
        j=0 => prod *= (3-1)/(2-1) = 2
        j=1 no entra i=j
        j=2 => prod *= (3-3)/(2-3) = 0
        coefficients[2] += 0*coef[1] = 0
    i=2
        prod = 1
        j=0 => prod *= (3-1)/(3-1) = 1
        j=1 => prod *= (3-2)/(3-2) = 1
        j=2 no entra i=j
        coefficients[2] += 1*coef[2] = 4

    coefficients = [2,3,4]
  







