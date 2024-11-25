#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <climits>
#include <iomanip>
#include <numeric>
using namespace std;
#define int long long
#define double long double
#define vi vector <int>
#define vb vector <bool>
#define vs vector <string>
#define vvi vector <vi>
#define vvb vector <vb>
#define vvs vector <vs>
#define all(x) x.begin(), x.end()
#define	rall(x) x.rbegin(), x.rend()
#define endl '\n'
const int mod = 1e9+7;
const int maxn = 1e5 + 10;

// problem : Have you ever heard of the Fibonacci numbers? Now, let's introduce you to the Tribonacci numbers. The Tribonacci sequence is defined as follows:

// 𝑇(0)=0
// 𝑇(1)=1
// 𝑇(2)=1

// For 𝑛>2
// , the Tribonacci number is given by the following formula 𝑇(𝑛)=𝑇(𝑛−1)+𝑇(𝑛−2)+𝑇(𝑛−3)

// Given an integer 𝑁
// (0≤𝑁≤109), your task is to calculate 𝑇(𝑁). Since the value of 𝑇(𝑁) can grow very large, you should output the result modulo 109+7

// The input contains a single integer 𝑁
// (0≤𝑁≤109)
// which represents the index of the Tribonacci number you need to calculate.
// Output : Print a single integer — the 𝑁𝑡ℎ : Tribonacci number modulo 109+7.


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

void	solve()
{
    int n; cin >> n;
    vector <vector<int>> mat = {{1, 1, 1}, {1, 0, 0}, {0, 1, 0}};
    vector<vector<int>> M = {{1}, {1}, {0}};
    if (n <= 2) cout << n - (n == 2) << endl;
    else {
        mat = power(mat, n - 2);
        multiply(mat, M);
        cout << mat[0][0] << endl;
    }
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}


