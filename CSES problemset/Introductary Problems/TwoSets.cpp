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
    int sum = n * (n + 1) / 2;
    if (sum & 1) {
        cout << "NO\n";
        return 0;
    }
    vector<int> a, b;
    int need = sum / 2;
    for (int i = n; i >= 1; i--) {
        if (need >= i) {
            a.push_back(i);
            need -= i;
        }
        else b.push_back(i);
    }
    cout << "YES\n";
    cout << a.size() << endl;
    for (int i : a) cout << i << ' '; cout << endl;
    cout << b.size() << endl;
    for (int i : b) cout << i << ' '; cout << endl;
}