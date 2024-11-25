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

// prblink: https://cses.fi/problemset/task/1096

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
    vector<int> M(6);
    for(int j = 1; j <= 6; j++) M[j - 1] = 1;
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i - 1 - j >= 0) M[i - 1] = (M[i - 1] + M[i - 1 - j]) % mod;
        }
    }
    if (n <= 6) {
        cout << M[n - 1] << endl;
        return ;
    }
    vector<vector<int>> mat(6, vector<int>(6));
    for(int j = 0; j < 6; j++) mat[0][j] = 1;
    for(int i = 1; i < 6; i++) mat[i][i - 1] = 1;

    mat = power(mat, n - 6);
    vector<vector<int>> MM(6, vector<int>(1));
    for(int i = 0; i < 6; i++){
        MM[i][0] = M[5 - i];
    }
    //   for(vi &v:MM){
    //     for(int i : v) cerr << i << ' ';
    //     cerr << endl;
    // }
    multiply(mat, MM);
    cout << mat[0][0] << endl;
}
 
int32_t	main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
}
