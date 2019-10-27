//
// Created by DELL on 2019/10/27.
//
#include <bits/stdc++.h>
using namespace std;
const int MAXN  = 100;
struct Matrix{
    // a[0..n-1] 表示一个方程
    // a[][0 .. m-2] 表示有m-1个未知数，每行是对应的系数
    // a[][m-1]是等式右边的值。
    double a[MAXN][MAXN], n, m;
    void gauss(){
        for (int i = 0; i < n; i++){
            int k = i;
            for (int j = i + 1; j < n; j++){
                if (abs(a[j][i]) > abs(a[k][i]))k = j;
            }
            for (int j = i; j < m; j++)
                swap(a[i][j], a[k][j]);
            for (int j = i + 1; j < n; j++){
                double r = a[j][i] / a[i][i];
                for (int k = i + 1; k < m; k++)
                    a[j][k] -= r*a[i][k];
            }
        }
        for (int i = n - 1; i >= 0; i--){
            for (int k = n; k < m; k++){
                for (int j = i + 1; j < n; j++)
                    a[i][k] -= a[i][j] * a[j][k];
                a[i][k] /= a[i][i];
            }
        }
    }
    double det(){
        int s = 0;
        for (int i = 0; i < n; i++){
            int k = i;
            for (int j = i + 1; j < n; j++){
                if (abs(a[j][i]) > abs(a[k][i]))k = j;
            }
            s += k == i;
            for (int j = i; j < m; j++)
                swap(a[i][j], a[k][j]);
            for (int j = i + 1; j < n; j++){
                double r = a[j][i] / a[i][i];
                for (int k = i + 1; k < m; k++)
                    a[j][k] -= r*a[i][k];
            }
        }
        double ret = 1;
        for (int i = 0; i < n; i++)
            ret *= a[i][i];
        return s & 1 ? -ret : ret;
    }
};
int main(){
    Matrix mat;
    mat.a[0][0] = 1;mat.a[0][1] = 2;mat.a[0][2] = 3;mat.a[0][3] = 100;
    mat.a[1][0] = 1;mat.a[1][1] = 1;mat.a[1][2] = 0;mat.a[1][3] = 20;
    mat.a[2][0] = 1;mat.a[2][1] = 0;mat.a[2][2] = 1;mat.a[2][3] = 10;
    mat.n = 3;
    mat.m = 4;
    mat.gauss();
    for (int i=0;i<3;i++){
        cerr<<mat.a[i][3]<<endl;
    }
}