#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

vector<vector<double>> transpose(const vector<vector<double>>& mat) {
    int rows = mat.size();
    int cols = mat[0].size();
    vector<vector<double>> result(cols, vector<double>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[j][i] = mat[i][j];
        }
    }

    return result;
}

vector<vector<double>> multiply(const vector<vector<double>>& a, const vector<vector<double>>& b) {
    int m = a.size();
    int n = a[0].size();
    int p = b[0].size();
    vector<vector<double>> result(m, vector<double>(p, 0.0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

vector<vector<double>> inverse(vector<vector<double>> mat) {
    int n = mat.size();
    vector<vector<double>> inv(n, vector<double>(n, 0.0));

    // 创建单位矩阵
    for (int i = 0; i < n; ++i) {
        inv[i][i] = 1.0;
    }

    // 高斯 - 约当消元法
    for (int i = 0; i < n; ++i) {
        // 部分主元
        double maxEl = abs(mat[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(mat[k][i]) > maxEl) {
                maxEl = abs(mat[k][i]);
                maxRow = k;
            }
        }

        // 交换行
        for (int k = i; k < n; ++k) {
            swap(mat[maxRow][k], mat[i][k]);
        }
        for (int k = 0; k < n; ++k) {
            swap(inv[maxRow][k], inv[i][k]);
        }

        // 归一化行
        double div = mat[i][i];
        for (int k = i; k < n; ++k) {
            mat[i][k] /= div;
        }
        for (int k = 0; k < n; ++k) {
            inv[i][k] /= div;
        }

        // 消去其他行
        for (int k = 0; k < n; ++k) {
            if (k != i && mat[k][i] != 0) {
                double factor = mat[k][i];
                for (int j = i; j < n; ++j) {
                    mat[k][j] -= factor * mat[i][j];
                }
                for (int j = 0; j < n; ++j) {
                    inv[k][j] -= factor * inv[i][j];
                }
            }
        }
    }

    return inv;
}

void printMatrix(const vector<vector<double>>& mat, const string& name, bool isVector = false) {
    cout << name << ":" << endl;
    if (isVector) {
        for (const auto& row : mat) {
            for (double val : row) {
                cout << fixed << setprecision(5) << val << endl;
            }
        }
    } else {
        for (const auto& row : mat) {
            for (double val : row) {
                cout << fixed << setprecision(5) << val << " ";
            }
            cout << endl;
        }
    }
}

void leastSquaresFit(const vector<double>& x, const vector<double>& y, int degree) {
    int n = x.size();
    int m = degree + 1;

    // 构造矩阵A
    vector<vector<double>> A(n, vector<double>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            A[i][j] = pow(x[i], j);
        }
    }

    // 计算A^T * A
    vector<vector<double>> AT = transpose(A);
    vector<vector<double>> ATA = multiply(AT, A);

    // 计算A^T * y
    vector<vector<double>> y_mat(n, vector<double>(1));
    for (int i = 0; i < n; ++i) {
        y_mat[i][0] = y[i];
    }
    vector<vector<double>> ATy = multiply(AT, y_mat);

    // 输出法方程组系数矩阵A和常量b
    printMatrix(ATA, "A");
    printMatrix(ATy, "b", true);

    // 计算系数x = (A^T A)^-1 A^T y
    vector<vector<double>> ATA_inv = inverse(ATA);
    vector<vector<double>> coefficients = multiply(ATA_inv, ATy);

    // 输出多项式系数
    printMatrix(coefficients, "x", true);
}

int main() {
    vector<double> x, y;
    double val;
    int degree;

    // 读取x值
    while (cin >> val) {
        x.push_back(val);
        if (cin.get() == '\n') break;
    }

    // 读取y值
    while (cin >> val) {
        y.push_back(val);
        if (cin.get() == '\n') break;
    }

    // 读取多项式阶数
    cin >> degree;

    leastSquaresFit(x, y, degree);

    return 0;
}    