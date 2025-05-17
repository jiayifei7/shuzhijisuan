#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100
#define EPSILON 1e-10

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

void gaussian_elimination(double A[MAX_SIZE][MAX_SIZE], double b[MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > fabs(A[max_row][i])) {
                max_row = k;
            }
        }

        if (max_row != i) {
            for (int k = 0; k < n; k++) {
                swap(&A[i][k], &A[max_row][k]);
            }
            swap(&b[i], &b[max_row]);
        }

        if (fabs(A[i][i]) < EPSILON) {
            printf("None!\n");
            exit(1);
        }

        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            b[i] -= A[i][j] * b[j];
        }
        b[i] /= A[i][i];
    }
}

int main() {
    double A[MAX_SIZE][MAX_SIZE], b[MAX_SIZE];
    int n = 0; 
    char line[MAX_SIZE * 20]; 

    fgets(line, sizeof(line), stdin);

    char *ptr = line;
    int count = 0;
    while (*ptr != '\0' && *ptr != '\n') {
        A[0][count++] = strtod(ptr, &ptr); 
    }

    n = (int)sqrt(count);
    if (n * n != count) {
        printf("None!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = A[0][i * n + j];
        }
    }

    fgets(line, sizeof(line), stdin);

    ptr = line;
    for (int i = 0; i < n; i++) {
        b[i] = strtod(ptr, &ptr);
    }

    gaussian_elimination(A, b, n);

    for (int i = 0; i < n; i++) {
        printf("%.5lf\n", b[i]);
    }

    return 0;
}