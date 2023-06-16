#include "./modularOperations.h"



int module(int a){
    return a % MODULE;
}

int inverse(int a) {
    return inverses[a % MODULE];
}

int divideBy(int a, int b) {
    return (a * inverse(b)) % MODULE;
}

int multiplyBy(int a, int b) {
    return (a * b) % MODULE;
}

int sum(int a, int b) {
    return (a + b) % MODULE;
}

int substract(int a, int b) {
    return (a - b) % MODULE;
}


