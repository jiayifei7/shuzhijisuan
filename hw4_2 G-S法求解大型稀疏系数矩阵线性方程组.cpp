#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

// 分割字符串为double向量，支持逗号分隔
vector<double> parseInput(const string& line) 
{
    vector<double> result;
    stringstream ss(line);
    string item;
    
    while (getline(ss, item, ',')) 
    {
        stringstream itemStream(item);
        double num;
        if (itemStream >> num) {
            result.push_back(num);
        }
    }
    return result;
}

// 计算无穷范数
double infinityNorm(const vector<double>& v1, const vector<double>& v2) 
{
    double maxDiff = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        maxDiff = max(maxDiff, fabs(v1[i] - v2[i]));
    }
    return maxDiff;
}

// 高斯-赛德尔迭代求解三对角线矩阵方程组
vector<double> gsSolve(int n, const vector<double>& b, double eps = 1e-5, int maxIter = 100000) 
{
    // 初始化解向量为零向量
    vector<double> x(n, 0.0);
    vector<double> x_old(n, 0.0);
    
    int iter = 0;
    double error;
    
    do {
        x_old = x;
        
        // 第一个方程
        x[0] = (b[0] + x_old[1]) / 4.0;
        
        // 中间方程
        for (int i = 1; i < n - 1; ++i) {
            x[i] = (b[i] + x[i-1] + x_old[i+1]) / 4.0;
        }
        
        // 最后一个方程
        x[n-1] = (b[n-1] + x[n-2]) / 4.0;
        
        // 计算误差
        error = infinityNorm(x, x_old);
        
        iter++;
    } while (error >= eps && iter < maxIter);
    
    return x;
}

int main() 
{
    // 读取向量b
    string line;
    if (getline(cin, line)) {
        vector<double> b = parseInput(line);
        int n = b.size();
        
        // 使用G-S法求解
        vector<double> solution = gsSolve(n, b);
        
        // 输出结果（保留整数）
        for (int i = 0; i < n; ++i) {
            cout << round(solution[i]);
            if (i < n - 1) {
                cout << ",";
            }
        }
        cout << endl;
    }
    
    return 0;
}