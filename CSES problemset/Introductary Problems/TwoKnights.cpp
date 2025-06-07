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
#include <cstring>
#include <climits>
#include <sstream>
#include <iomanip>
#include <numeric>
using namespace std;
#define int long long
#define double long double
#define all(x) x.begin(), x.end()
#define	rall(x) x.rbegin(), x.rend()
#define endl '\n'
 
 
int32_t	main()
{
    int n; cin >> n;
    for (int k = 1; k <= n; k++) {
        int nn = k * k;
        int ans = nn * (nn - 1) / 2;
        if (k >= 2) ans -= (k - 2) * (k - 1) * 4;
        cout << ans << endl;
    }
}
