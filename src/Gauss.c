#include <stdio.h>
#include <stdlib.h>

#define MOD 251

typedef struct {
    int x;
    int y;
} Point;

int mod(int n) {
    return (n % MOD + MOD) % MOD;
}

int modInverse(int n) {
    int t = 0;
    int newT = 1;
    int r = MOD;
    int newR = n;

    while (newR != 0) {
        int quotient = r / newR;

        int temp = newT;
        newT = mod(t - mod(quotient * newT));
        t = temp;

        temp = newR;
        newR = mod(r - mod(quotient * newR));
        r = temp;
    }

    if (r > 1) {
        // printf("Error: Inverse does not exist\n");
        return -1;
    }

    if (t < 0) {
        t = mod(t + MOD);
    }

    return t;
}

void polynomialCoefficients(Point* points, int* coefficients, int degree) {
    int n = degree + 1;

    // Initialize matrix and vector
    int** matrix = (int**)malloc(n * sizeof(int*));
    int* vector = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        vector[i] = mod(points[i].y);
    }

    // Calculate matrix elements
    for (int i = 0; i < n; i++) {
        int x = points[i].x;
        int xPower = 1;
        for (int j = 0; j < n; j++) {
            matrix[i][j] = xPower;
            xPower = mod(xPower * x);
        }
    }

    // Gaussian elimination
    for (int i = 0; i < n; i++) {
        int pivotIndex = -1;
        for (int j = i; j < n; j++) {
            if (matrix[j][i] != 0) {
                pivotIndex = j;
                break;
            }
        }

        if (pivotIndex == -1) {
            // printf("Error: Singular matrix\n");
            return;
        }

        // Swap rows
        if (pivotIndex != i) {
            for (int j = i; j < n; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[pivotIndex][j];
                matrix[pivotIndex][j] = temp;
            }
            int temp = vector[i];
            vector[i] = vector[pivotIndex];
            vector[pivotIndex] = temp;
        }

        // Elimination
        int pivot = matrix[i][i];
        for (int j = i + 1; j < n; j++) {
            int factor = mod(matrix[j][i] * modInverse(pivot));
            for (int k = i; k < n; k++) {
                matrix[j][k] = mod(matrix[j][k] - mod(factor * matrix[i][k]));
            }
            vector[j] = mod(vector[j] - mod(factor * vector[i]));
        }
    }

    // Back substitution
    for (int i = n - 1; i >= 0; i--) {
        coefficients[i] = vector[i];
        for (int j = i + 1; j < n; j++) {
            coefficients[i] = mod(coefficients[i] - mod(matrix[i][j] * coefficients[j]));
        }
        coefficients[i] = mod(coefficients[i] * modInverse(matrix[i][i]));
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
}


int check(Point p, int * coefficients, int degree){
    int result = 0;
    int temp = 1;
    printf("\n");
    for(int i = 0; i < degree+1; i++){
        printf("%d * %d^%d + ", coefficients[i], p.x, i);
        result += coefficients[i] * temp;
        temp *= p.x;
    }
    printf("\n");
    result = result % MOD;
    printf("Result: %d\n", result);
    if(result == p.y){
        return 1;
    }

    return 0;
}
