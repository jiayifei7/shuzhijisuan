/*
【问题描述】给定一组数据(xi, yi)，采用多项式进行拟合
【输入形式】输入xi，yi，多项式阶数n
【输出形式】法方程组系数矩阵A，常量b，多项式系数x（保留5位小数）
【样例输入】

1 2 4 6 8 10

1.8 3.7 8.2 12.0 15.8 20.2

1

【样例输出】

A:

6.00000 31.00000

31.00000 221.00000

b:

61.70000

442.40000

x:

-0.21562

2.03205
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

// 求解三对角矩阵方程组
vector<double> solveTridiagonal(const vector<double>& a, const vector<double>& b, 
                              const vector<double>& c, const vector<double>& d) {
    int n = d.size();
    vector<double> x(n), p(n), q(n);
    
    // 追的过程
    p[0] = -c[0] / b[0];
    q[0] = d[0] / b[0];
    
    for (int i = 1; i < n; i++) {
        double m = b[i] + a[i] * p[i-1];
        p[i] = -c[i] / m;
        q[i] = (d[i] - a[i] * q[i-1]) / m;
    }
    
    // 赶的过程
    x[n-1] = q[n-1];
    for (int i = n-2; i >= 0; i--) {
        x[i] = p[i] * x[i+1] + q[i];
    }
    
    return x;
}

// 计算三次样条插值
double cubicSpline(const vector<double>& x, const vector<double>& y, 
                  const vector<double>& M, double xi) {
    int n = x.size();
    
    // 找到xi所在的区间
    int i = 0;
    while (i < n-1 && xi > x[i+1]) i++;
    
    // 计算hi
    double h = x[i+1] - x[i];
    
    // 计算插值
    double t = (xi - x[i]) / h;
    double t1 = 1 - t;
    
    return y[i] * t1 + y[i+1] * t + 
           ((t1*t1*t1 - t1) * M[i] + (t*t*t - t) * M[i+1]) * h*h / 6.0;
}

int main() {
    // 读取数据点
    vector<double> x, y;
    double val;
    string line;
    
    // 读取x坐标
    getline(cin, line);
    stringstream ss_x(line);
    while (ss_x >> val) {
        x.push_back(val);
    }
    
    // 读取y坐标
    getline(cin, line);
    stringstream ss_y(line);
    while (ss_y >> val) {
        y.push_back(val);
    }
    
    // 读取边界条件
    double m0, mn;
    cin >> m0 >> mn;
    
    // 读取待求点
    double xi;
    cin >> xi;
    
    int n = x.size();
    
    // 构造三对角矩阵方程组
    vector<double> a(n), b(n), c(n), d(n);
    
    // 第一个方程（使用第一类边界条件）
    b[0] = 2 * (x[1] - x[0]);
    c[0] = x[1] - x[0];
    d[0] = 6 * ((y[1] - y[0]) / (x[1] - x[0]) - m0);
    
    // 中间方程
    for (int i = 1; i < n-1; i++) {
        double hi = x[i] - x[i-1];
        double hi1 = x[i+1] - x[i];
        
        a[i] = hi;
        b[i] = 2 * (hi + hi1);
        c[i] = hi1;
        d[i] = 6 * ((y[i+1] - y[i]) / hi1 - (y[i] - y[i-1]) / hi);
    }
    
    // 最后一个方程（使用第一类边界条件）
    a[n-1] = x[n-1] - x[n-2];
    b[n-1] = 2 * (x[n-1] - x[n-2]);
    d[n-1] = 6 * (mn - (y[n-1] - y[n-2]) / (x[n-1] - x[n-2]));
    
    // 求解方程组得到二阶导数
    vector<double> M = solveTridiagonal(a, b, c, d);
    
    // 输出二阶导数
    cout << fixed << setprecision(5);
    for (double m : M) {
        cout << m << endl;
    }
    
    // 计算并输出插值
    double result = cubicSpline(x, y, M, xi);
    cout << result << endl;
    
    return 0;
}