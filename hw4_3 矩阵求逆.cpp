#include <stdio.h>
#define N 3

void printMatrix(float mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.5f ", mat[i][j]);
        }
        printf("\n");
    }
}

void matrixInverse(float A[N][N]) {
    float W[N][2*N];
    float temp;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            W[i][j] = A[i][j];
        }
        for (int j = N; j < 2*N; j++) {
            W[i][j] = (j - N == i) ? 1.0f : 0.0f;
        }
    }
    
    for (int k = 0; k < N; k++) {

        int max_row = k;
        for (int i = k + 1; i < N; i++) {
            if (W[i][k] > W[max_row][k]) {
                max_row = i;
            }
        }
        
        if (max_row != k) {
            for (int j = 0; j < 2*N; j++) {
                temp = W[k][j];
                W[k][j] = W[max_row][j];
                W[max_row][j] = temp;
            }
        }
        
        if (W[k][k] == 0.0f) {
            printf("Matrix is not invertible.\n");
            return;
        }
        
        temp = W[k][k];
        for (int j = k; j < 2*N; j++) {
            W[k][j] /= temp;
        }
        
        for (int i = 0; i < N; i++) {
            if (i != k && W[i][k] != 0.0f) {
                temp = W[i][k];
                for (int j = k; j < 2*N; j++) {
                    W[i][j] -= W[k][j] * temp;
                }
            }
        }
    }
    
    float inverse[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inverse[i][j] = W[i][j + N];
        }
    }
    
    printMatrix(inverse);
}

int main() {
    float A[N][N];
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%f", &A[i][j]);
        }
    }
    
    matrixInverse(A);
    
    return 0;
}