#include <stdio.h>
#include <stdlib.h>

#define N 6 

double x[N] = {0.0, 0.1, 0.195, 0.3, 0.401, 0.5};
double y[N] = {0.39894, 0.39695, 0.39142, 0.38138, 0.36812, 0.35206};

double lagrange_interpolation(double x_val) {
    double result = 0.0;
    
    for (int i = 0; i < N; i++) {
        double term = y[i];
        for (int j = 0; j < N; j++) {
            if (j != i) {
                term *= (x_val - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    
    return result;
}

int main() {
    double x_val;
    
    scanf("%lf", &x_val);
    
    double result = lagrange_interpolation(x_val);
    
    printf("%.5f\n", result);
    
    return 0;
}