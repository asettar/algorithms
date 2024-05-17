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

//prblink : https://codeforces.com/gym/102644/problem/B

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
    if(n == 1) {
        cout << 19 << endl;
        return ;
    }
    // vector<vector<int>> dp(n + 1, vector<int>(2));
    // dp[0][1] = 1;
    // for(int i = 1; i <= n; i++) {
     
    //     dp[i][1] += ((6 * dp[i-1][0]) % mod + (19 * dp[i-1][1]) % mod) % mod;
    //     dp[i][0] += ((20 * dp[i-1][0]) % mod + (7 * dp[i-1][1]) % mod) % mod;
    // }
    // cerr << dp[n][0] << ' ' << dp[n][1] << endl;
    vector<vector<int>> A = {{20, 7}, {6, 19}};
    A = power(A, n-1);
    vector<int> M = {7, 19};
    int ans = 0;
    for(int i = 0; i < 2; i++) ans = (ans + (A[1][i] * M[i]) % mod) % mod;
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