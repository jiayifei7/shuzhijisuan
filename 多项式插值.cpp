#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 100
#define PRECISION 5

void read_points(double x[], double y[], int *n) {
    char line[1000];
    int count = 0;
    
    fgets(line, sizeof(line), stdin);
    char *token = strtok(line, " \n");
    while (token != NULL) {
        x[count++] = atof(token);
        token = strtok(NULL, " \n");
    }
    
    count = 0;
    fgets(line, sizeof(line), stdin);
    token = strtok(line, " \n");
    while (token != NULL) {
        y[count++] = atof(token);
        token = strtok(NULL, " \n");
    }
    
    *n = count - 1;
}

void lagrange_interpolation(double x[], double y[], int n, double coeffs[]) {

    for (int i = 0; i <= n; i++) {
        coeffs[i] = 0.0;
    }
    
    double temp[n+2];
    double term_coeffs[n+1];
    
    for (int i = 0; i <= n; i++) {

        double denom = 1.0;
        for (int j = 0; j <= n; j++) {
            if (i != j) {
                denom *= (x[i] - x[j]);
            }
        }
        
        for (int k = 0; k <= n; k++) {
            term_coeffs[k] = 0.0;
        }
        term_coeffs[0] = y[i] / denom;
        
        for (int j = 0; j <= n; j++) {
            if (j == i) continue;
            
            for (int k = 0; k <= n+1; k++) {
                temp[k] = 0.0;
            }
            
            for (int k = 0; k <= n; k++) {
                temp[k+1] += term_coeffs[k];
                temp[k] += -x[j] * term_coeffs[k];
            }
            
            for (int k = 0; k <= n; k++) {
                term_coeffs[k] = temp[k];
            }
        }
        
        for (int k = 0; k <= n; k++) {
            coeffs[k] += term_coeffs[k];
        }
    }
}

int main() {
    double x[MAX_POINTS], y[MAX_POINTS];
    int n;
    
    read_points(x, y, &n);
    
    double coeffs[MAX_POINTS];
    lagrange_interpolation(x, y, n, coeffs);
    
    for (int i = 0; i <= n; i++) {
        printf("%.*f\n", PRECISION, coeffs[i]);
    }
    
    return 0;
}