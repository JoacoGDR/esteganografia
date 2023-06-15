#include "./modularOperations.h"

int inverse(int a) {
    return inverses[a];
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


