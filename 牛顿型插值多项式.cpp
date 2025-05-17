#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 10

void print_table(double table[MAX_POINTS][MAX_POINTS], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            printf("%.5f ", table[i][j]);
        }
        for (int j = n - i; j < n; j++) {
            printf("0.00000 ");
        }
        printf("\n");
    }
}

void divided_differences(double x[], double y[], double dd[MAX_POINTS][MAX_POINTS], int n) {
    for (int i = 0; i < n; i++) {
        dd[i][0] = y[i];
    }
    
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            dd[i][j] = (dd[i+1][j-1] - dd[i][j-1]) / (x[i+j] - x[i]);
        }
    }
}

void finite_differences(double x[], double y[], double fd[MAX_POINTS][MAX_POINTS], int n) {
    for (int i = 0; i < n; i++) {
        fd[i][0] = y[i];
    }
    
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            fd[i][j] = fd[i+1][j-1] - fd[i][j-1];
        }
    }
}

double newton_interpolation(double x[], double dd[MAX_POINTS][MAX_POINTS], int n, double x_val) {
    double result = dd[0][0];
    double term = 1.0;
    
    for (int i = 1; i < n; i++) {
        term *= (x_val - x[i-1]);
        result += dd[0][i] * term;
    }
    
    return result;
}

int main() {
    double x[MAX_POINTS], y[MAX_POINTS];
    double x_val;
    int n = 0;
    
    while (scanf("%lf", &x[n]) == 1) {
        n++;
        if (getchar() == '\n') break;
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%lf", &y[i]);
    }
    
    scanf("%lf", &x_val);
    
    double dd[MAX_POINTS][MAX_POINTS];
    divided_differences(x, y, dd, n);
    
    print_table(dd, n);
    
    double result_dd = newton_interpolation(x, dd, n, x_val);
    printf("%.5f\n", result_dd);
    
    double fd[MAX_POINTS][MAX_POINTS];
    finite_differences(x, y, fd, n);
    
    print_table(fd, n);
    
    double h = x[1] - x[0];
    double s = (x_val - x[0]) / h;
    double result_fd = fd[0][0];
    double term = 1.0;
    
    for (int i = 1; i < n; i++) {
        term *= (s - (i-1)) / i;
        result_fd += fd[0][i] * term;
    }
    
    printf("%.5f\n", result_fd);
    
    return 0;
}