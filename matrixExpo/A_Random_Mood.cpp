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

//prblink : https://codeforces.com/gym/102644/problem/A

void    multiply(vector<vector<double>> &a, vector<vector<double>> &b) {
    double n = a.size(), m = b[0].size(), p = a[0].size();
    vector<vector<double>> res(n, vector<double>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int k = 0; k < p; k++) {
                res[i][j] = (res[i][j] + (a[i][k] * b[k][j]));
            }
        }
    }
    a = res;
}

vector<vector<double>>    power(vector<vector<double>> &mat, int n) {
    vector<vector<double>> res(mat.size(), vector<double>(mat[0].size()));
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
    double n, p; cin >> n >> p;
    vector<vector<double>> M = {{p, 0}, {1 - p, 1}};
    cout << fixed << setprecision(10);
    if (n == 1) {
        double ans = 1 - p;
        cout << ans << endl;
        return ;
    }
    vector<vector<double>> A = {{1 - p, p}, {p, 1 - p}};
    A = power(A, n - 1);
    double ans = 0;
    for(int i = 0; i < 2; i++) {
        ans += A[1][i] * M[i][0];
    }
    cout << ans << endl;
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

// 0: 1
// 0: 0

// 1: 0.3
// 1: 0.7

// 

