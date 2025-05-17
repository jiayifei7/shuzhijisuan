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
    
    // 读取矩阵A的一行输入
    fgets(input, sizeof(input), stdin);
    
    // 计算矩阵阶数n
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
        printf("错误：输入的元素数量不是完全平方数！\n");
        return 1;
    }
    
    // 分配内存
    A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }
    b = (double *)malloc(n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    
    // 填充矩阵A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = temp_values[i * n + j];
        }
    }
    
    // 读取向量b
    fgets(input, sizeof(input), stdin);
    token = strtok(input, " \n");
    for (int i = 0; i < n; i++) {
        if (token == NULL) {
            printf("错误：输入的元素不足！\n");
            return 1;
        }
        b[i] = atof(token);
        token = strtok(NULL, " \n");
    }
    
    // 读取初始解x
    fgets(input, sizeof(input), stdin);
    token = strtok(input, " \n");
    for (int i = 0; i < n; i++) {
        if (token == NULL) {
            printf("错误：输入的元素不足！\n");
            return 1;
        }
        x[i] = atof(token);
        token = strtok(NULL, " \n");
    }
    
    // 调用Jacobi方法
    jacobi(n, A, b, x);
    
    // 输出结果（修改为"x:"开头）
    printf("x:\n");
    for (int i = 0; i < n; i++) {
        printf("%.5f\n", x[i]);
    }
    
    // 释放内存
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);
    
    return 0;
}

