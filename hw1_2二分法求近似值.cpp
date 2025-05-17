#include <stdio.h>
#include <math.h>

double f(double x)
{
    return exp(x) + 10 * x - 2;      //方程 exp=e^x
}

int main()
{
    double a = 0.0, b = 1.0;         //两个端点
    double eps = 0.5e-3;             //0.0005    区间长度
    double c, fa = f(a), fc;

    while (b - a >= eps)
    {
        c = (a + b) / 2;
        fc = f(c);
        if (fc == 0)
        {
            a = c;
            b = c;
            break;
        }
        if (fa * fc < 0)
        {
            b = c;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }

    c = (a + b) / 2;             //区间达到足够小后，再次计算中点值当作零点
    fc = f(c);

    printf("%.5lf, %.9lf\n", c, fc);

    return 0;
}