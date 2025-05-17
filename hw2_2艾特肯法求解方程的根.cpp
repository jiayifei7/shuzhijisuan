#include <stdio.h>
#include <math.h>

double iterate(double x, double a, double b) {
    return a * x * x * x + b;
}

void aitken_method(double a, double b, double x0, double tolerance) {
    double x_prev = x0;
    double y, z, x_next;
    int iteration = 0;

    while (1) {
    	
        y = iterate(x_prev, a, b);
        z = iterate(y, a, b);

        x_next = x_prev - pow(y - x_prev, 2) / (z - 2 * y + x_prev);

        if (fabs(x_next - x_prev) < tolerance) {
            printf("%.6lf, %.6lf, %.6lf\n", y, z, x_next);
            break;
        }

        x_prev = x_next;
        iteration++;

        if (iteration > 1000) {
            printf("None!\n");
            break;
        }
    }
}

int main() {
    double a, b, x0;
    double tolerance = 1e-5;

    scanf("%lf %lf %lf", &a, &b, &x0);

    aitken_method(a, b, x0, tolerance);

    return 0;
}
