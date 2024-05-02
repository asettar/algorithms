#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
const int mod = 1e9+7;
const int maxn = 1e5 + 10;

void    multiply(vector<vector<int>> &a, vector<vector<int>> &b) {
    int n = a.size(), m = b[0].size(), p = a[0].size();
    vector<vector<int>> res(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int k = 0; k < p; k++) {
                res[i][j] = (res[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
            }
        }
    }
    a = res;
}

vector<vector<int>>    power(vector<vector<int>> &mat, int n) {
    vector<vector<int>> res(mat.size(), vector<int>(mat[0].size()));
    for(int i = 0; i < mat.size(); i++) res[i][i] = 1;
    while (n > 0) {
        if (n & 1)
            multiply(res, mat);
        multiply(mat, mat);
        n >>= 1;
    }
    return res;
}

