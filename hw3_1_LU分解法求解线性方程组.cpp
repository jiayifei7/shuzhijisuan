#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 10
#define PRECISION 5

void print_matrix(double mat[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.*f ", PRECISION, mat[i][j]);
        }
        printf("\n");
    }
}

void print_vector(double vec[MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        printf("%.*f\n", PRECISION, vec[i]);
    }
}

int main() {
    double A[MAX_SIZE][MAX_SIZE], L[MAX_SIZE][MAX_SIZE], U[MAX_SIZE][MAX_SIZE];
    double b[MAX_SIZE], y[MAX_SIZE], x[MAX_SIZE];
    double A_elements[MAX_SIZE * MAX_SIZE];
    double b_elements[MAX_SIZE];
    char line[1024];
    int n = 0;
    int count = 0;
    char *token;

    fgets(line, sizeof(line), stdin);
    
    token = strtok(line, " ");
    while (token != NULL && count < MAX_SIZE * MAX_SIZE) {
        A_elements[count++] = atof(token);
        token = strtok(NULL, " ");
    }

    n = (int)sqrt(count);
    if (n * n != count) {
        fprintf(stderr, "NULL!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = A_elements[i * n + j];
        }
    }

    fgets(line, sizeof(line), stdin);
    
    count = 0;
    token = strtok(line, " ");
    while (token != NULL && count < MAX_SIZE) {
        b_elements[count++] = atof(token);
        token = strtok(NULL, " ");
    }

    if (count != n) {
        fprintf(stderr, "NULL!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        b[i] = b_elements[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) L[i][j] = 1.0;
            else L[i][j] = 0.0;
            U[i][j] = 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }

        for (int j = i + 1; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) {
                sum += L[j][k] * U[k][i];
            }
            if (fabs(U[i][i]) < 1e-10) {
                fprintf(stderr, "NULL!\n");
                return 1;
            }
            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }

    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = b[i] - sum;
    }

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    printf("L:\n");
    print_matrix(L, n);
    printf("U:\n");
    print_matrix(U, n);
    printf("y:\n");
    print_vector(y, n);
    printf("x:\n");
    print_vector(x, n);

    return 0;
}
