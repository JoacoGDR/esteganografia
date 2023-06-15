#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

void find_polynomial_coefficients(Point* points, int num_points, int degree, double* coefficients) {
    int i, j, k;
    double x_sum[2 * degree + 1];
    double y_sum[degree + 1];
    double matrix[degree + 1][degree + 2];

    // Initialize the sums of powers of x and y
    for (i = 0; i < 2 * degree + 1; i++) {
        x_sum[i] = 0.0;
    }
    for (i = 0; i < degree + 1; i++) {
        y_sum[i] = 0.0;
    }

    // Calculate the sums of powers of x and y
    for (i = 0; i < num_points; i++) {
        double temp_x = 1.0;
        for (j = 0; j < 2 * degree + 1; j++) {
            x_sum[j] += temp_x;
            temp_x *= points[i].x;
        }

        double temp_y = points[i].y;
        for (j = 0; j < degree + 1; j++) {
            y_sum[j] += temp_y;
            temp_y *= points[i].x;
        }
    }

    // Build the matrix for the least squares method
    for (i = 0; i < degree + 1; i++) {
        for (j = 0; j < degree + 1; j++) {
            matrix[i][j] = x_sum[i + j];
        }
        matrix[i][degree + 1] = y_sum[i];
    }

    // Gauss-Jordan elimination
    for (k = 0; k < degree + 1; k++) {
        for (i = k + 1; i < degree + 1; i++) {
            double factor = matrix[i][k] / matrix[k][k];
            for (j = k; j < degree + 2; j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }

    // Back substitution
    for (i = degree; i >= 0; i--) {
        coefficients[i] = matrix[i][degree + 1];
        for (j = i + 1; j < degree + 1; j++) {
            coefficients[i] -= matrix[i][j] * coefficients[j];
        }
        coefficients[i] /= matrix[i][i];
    }
}

int main() {
    Point points[] = {{1.0, 2.0}, {2.0, 5.0}, {3.0, 5.0},{9.0,5.0}};
    int num_points = sizeof(points) / sizeof(points[0]);
    int degree = num_points - 1;
    double coefficients[degree + 1];

    find_polynomial_coefficients(points, num_points, degree, coefficients);

    printf("Coefficients: ");
    for (int i = 0; i < degree + 1; i++) {
        printf("%.2f ", coefficients[i]);
    }
    printf("\n");

    return 0;
}
