#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 1000
#define MAX_ITER 1000
#define TOLERANCE 1e-5

void jacobi(int n, double **A, double *b, double *x) {
    double *x_new = (double *)malloc(n * sizeof(double));
    int iter = 0;
    double diff;
    
    do {
        diff = 0.0;
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
            
            if (fabs(x_new[i] - x[i]) > diff) {
                diff = fabs(x_new[i] - x[i]);
            }
        }
        
        for (int i = 0; i < n; i++) {
            x[i] = x_new[i];
        }
        
        iter++;
    } while (diff > TOLERANCE && iter < MAX_ITER);
    
    free(x_new);
}

int main() {
    char input[MAX_SIZE];
    double **A;
    double *b;
    double *x;
    int n = 0;
    
    // ��ȡ����A��һ������
    fgets(input, sizeof(input), stdin);
    
    // ����������n
    char *token = strtok(input, " \n");
    int count = 0;
    double temp_values[MAX_SIZE];
    
    while (token != NULL) {
        temp_values[count] = atof(token);
        count++;
        token = strtok(NULL, " \n");
    }
    
    n = (int)sqrt(count);
    if (n * n != count) {
        printf("���������Ԫ������������ȫƽ������\n");
        return 1;
    }
    
    // �����ڴ�
    A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }
    b = (double *)malloc(n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    
    // ������A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = temp_values[i * n + j];
        }
    }
    
    // ��ȡ����b
    fgets(input, sizeof(input), stdin);
    token = strtok(input, " \n");
    for (int i = 0; i < n; i++) {
        if (token == NULL) {
            printf("���������Ԫ�ز��㣡\n");
            return 1;
        }
        b[i] = atof(token);
        token = strtok(NULL, " \n");
    }
    
    // ��ȡ��ʼ��x
    fgets(input, sizeof(input), stdin);
    token = strtok(input, " \n");
    for (int i = 0; i < n; i++) {
        if (token == NULL) {
            printf("���������Ԫ�ز��㣡\n");
            return 1;
        }
        x[i] = atof(token);
        token = strtok(NULL, " \n");
    }
    
    // ����Jacobi����
    jacobi(n, A, b, x);
    
    // ���������޸�Ϊ"x:"��ͷ��
    printf("x:\n");
    for (int i = 0; i < n; i++) {
        printf("%.5f\n", x[i]);
    }
    
    // �ͷ��ڴ�
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);
    
    return 0;
}

