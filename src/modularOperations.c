#include "./modularOperations.h"

int module(int a){
    if(a < 0){
        return a % MODULE + MODULE;
    }
    return a % MODULE;
}

// int inverse(int a) {
//     return inverses_array[a % MODULE];
// }

// int divideBy(int a, int b) {
//     return (a * inverse(b)) % MODULE;
// }

int multiplyBy(int a, int b) {
    return (a * b) % MODULE;
}

int sum(int a, int b) {
    return (a + b) % MODULE;
}

int substract(int a, int b) {
    return (a - b) % MODULE;
}


