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
    int t; cin >> t;
    while (t--) {
        int r, c; cin >> r >> c;
        int mx = max(r, c);
        int cur = (mx - 1) * (mx - 1) + 1;
        if (cur & 1) {
            cur += c - 1;
            cur += abs(mx - r);
        }
        else {
            cur += r - 1;
            cur += abs(mx - c); 
        }
        cout << cur << endl;
    }
}
 