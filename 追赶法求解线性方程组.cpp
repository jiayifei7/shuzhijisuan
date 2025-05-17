#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100  

void print_matrix(double **mat, int n, const char *name) {
    printf("%s:\n", name);
    for (int i = 0; i < n; i++) {
        printf("%.5f", mat[i][0]);
        for (int j = 1; j < n; j++) {
            printf(" %.5f", mat[i][j]);
        }
        printf("\n");
    }
}

void print_vector(double *vec, int n, const char *name) {
    printf("%s:\n", name);
    for (int i = 0; i < n; i++) {
        printf("%.5f\n", vec[i]);
    }
}

void LU_decomposition(double **A, double **L, double **U, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = (i == j) ? 1.0 : 0.0;
            U[i][j] = 0.0;
        }
    }

    U[0][0] = A[0][0];
    if (n > 1) {
        U[0][1] = A[0][1];
    }

    for (int i = 1; i < n; i++) {
        L[i][i-1] = A[i][i-1] / U[i-1][i-1];
        U[i][i] = A[i][i] - L[i][i-1] * U[i-1][i];
        if (i < n-1) {
            U[i][i+1] = A[i][i+1];
        }
    }
}

void solve_linear_system(double **A, double *b, double *x, int n) {
    double **L = (double **)malloc(n * sizeof(double *));
    double **U = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        L[i] = (double *)malloc(n * sizeof(double));
        U[i] = (double *)malloc(n * sizeof(double));
    }

    LU_decomposition(A, L, U, n);

    print_matrix(L, n, "L");
    print_matrix(U, n, "U");

    double *y = (double *)malloc(n * sizeof(double));
    y[0] = b[0];
    for (int i = 1; i < n; i++) {
        y[i] = b[i] - L[i][i-1] * y[i-1];
    }
    print_vector(y, n, "y");

    x[n-1] = y[n-1] / U[n-1][n-1];
    for (int i = n-2; i >= 0; i--) {
        x[i] = (y[i] - U[i][i+1] * x[i+1]) / U[i][i];
    }

    for (int i = 0; i < n; i++) {
        free(L[i]);
        free(U[i]);
    }
    free(L);
    free(U);
    free(y);
}

int main() {
    double A_elements[MAX_SIZE * MAX_SIZE];
    double b[MAX_SIZE];
    double x[MAX_SIZE];
    double **A = NULL;
    int n = 0;
    int count = 0;
    char line[1024];
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

    A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            A[i][j] = A_elements[i * n + j];
        }
    }

    for (int i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }

    solve_linear_system(A, b, x, n);

    printf("x:\n");
    for (int i = 0; i < n; i++) {
        printf("%.5f\n", x[i]);
    }

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}