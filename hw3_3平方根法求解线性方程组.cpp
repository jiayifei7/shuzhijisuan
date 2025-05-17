#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

int count_numbers(const char *line) {
    int count = 0;
    int in_number = 0;
    
    for (int i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i]) || line[i] == '.' || line[i] == '+' || line[i] == '-') {
            if (!in_number) {
                count++;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
    }
    return count;
}

int read_input(double ***A, double **b, int *n) {
    char line[MAX_LINE_LENGTH];
    *n = 0;
    
    
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }
    
    *n = (int)sqrt(count_numbers(line));
    if (*n <= 0) {
        return 0;
    }
    
    *A = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        (*A)[i] = (double *)malloc(*n * sizeof(double));
    }
    *b = (double *)malloc(*n * sizeof(double));
    
    char *token = strtok(line, " \t\n");
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (token == NULL) {

                if (fgets(line, sizeof(line), stdin) == NULL) {
                    return 0;
                }
                token = strtok(line, " \t\n");
                if (token == NULL) {
                    return 0;
                }
            }
            (*A)[i][j] = atof(token);
            token = strtok(NULL, " \t\n");
        }
    }
    
    for (int i = 0; i < *n; i++) {
        if (token == NULL) {
            if (fgets(line, sizeof(line), stdin) == NULL) {
                return 0;
            }
            token = strtok(line, " \t\n");
            if (token == NULL) {
                return 0;
            }
        }
        (*b)[i] = atof(token);
        token = strtok(NULL, " \t\n");
    }
    
    return 1;
}

void standard_cholesky(int n, double **A, double *b, double *X) {
    double **L = (double **)malloc(n * sizeof(double *));
    double *y = (double *)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {
        L[i] = (double *)calloc(n, sizeof(double));
    }

    for (int j = 0; j < n; j++) {
        double sum = 0.0;
        for (int k = 0; k < j; k++) {
            sum += L[j][k] * L[j][k];
        }
        L[j][j] = sqrt(A[j][j] - sum);
        
        for (int i = j+1; i < n; i++) {
            sum = 0.0;
            for (int k = 0; k < j; k++) {
                sum += L[i][k] * L[j][k];
            }
            L[i][j] = (A[i][j] - sum) / L[j][j];
        }
    }

    printf("L:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.5f ", L[i][j]);
        }
        if (i < n-1) printf("\n");
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
    
    printf("y:\n");
    for (int i = 0; i < n; i++) {
        printf("%.5f\n", y[i]);
    }
    
    for (int i = n-1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i+1; j < n; j++) {
            sum += L[j][i] * X[j];  
        }
        X[i] = (y[i] - sum) / L[i][i];
    }
    
    printf("x:\n");
    for (int i = 0; i < n; i++) {
        printf("%.5f\n", X[i]);
    }
    
    for (int i = 0; i < n; i++) {
        free(L[i]);
    }
    free(L);
    free(y);
}

int main() {
    double **A = NULL;
    double *b = NULL;
    double *X = NULL;
    int n = 0;
    
    if (!read_input(&A, &b, &n)) {
        printf("NULL!\n");
        return 1;
    }
    
    X = (double *)malloc(n * sizeof(double));
    standard_cholesky(n, A, b, X);
    
    for (int i = 0; i < n; i++) free(A[i]);
    free(A);
    free(b);
    free(X);
    
    return 0;
}
