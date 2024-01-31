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

// prblink : https://arena.moi/problem/mnpc22mnpc2022zigzag
vvi dp;

struct segTree {
	set<pair<int, int>> identity;
	set<pair<int, int>> fn(set<pair<int, int>>& a, set<pair<int, int>> &b) {
		set<pair<int, int>> res;
		for(auto p : a)
			res.insert(p);
		for(auto p : b)
			res.insert(p);
		return res;
	}

	int n;
	vector<int> all;
	vector<set<pair<int, int>>> s;

	segTree(vector<int> &a) {
		n = a.size();
		s.resize(4 * n, identity);
		all = a;
		build(1, 0, n-1, 0, n-1);
	}

	void build(int node, int start, int end, const int l, const int r) {
		if (start > r || end < l)
			return ;
		
		if (start == end) {
			s[node].insert({all[start], start});
			return ;
		}

		int mid = (start + end) / 2;
		build(2*node, start, mid, l, r);
		build(2*node+1, mid + 1, end, l, r);
		s[node] = fn(s[2*node], s[2*node+1]);
	}

	// get the next pos in log^2(n)
	pair<int, int> get_positions(int node, int start, int end, const int val, const int l, const int r){
		if (start > r || end < l) return {1e9, 1e9};
		pair<int, int> res = {1e9, 1e9};
		if (start >= l && end <= r){
			auto it = s[node].upper_bound({val, 1e9});
			if (it != s[node].end())
				res.first = it->second;
			it = s[node].lower_bound({val, -1});
			if (it != s[node].begin()){
				it--;
				res.second = it->second;
			}
			return res;
		}
		int mid = (start + end) / 2;
		auto left = get_positions(2 * node, start, mid, val, l, r);
		auto right = get_positions(2 * node + 1, mid + 1, end, val, l, r);
		res = left;
		if (right.first != 1e9){
			if (res.first == 1e9 || all[res.first] > all[right.first]) res.first = right.first;
		}
		if (right.second != 1e9){
			if (res.second == 1e9 || all[res.second] < all[right.second]) res.second = right.second;
		}
		return res;
	}
	pair<int, int> get_positions(int val, int l, int r){
		return get_positions(1, 0, n - 1, val, l, r);
	}
};

int rec(int i, int jump, vector<int> &a, segTree &s){
	if (i == 1e9) return 0;
	if (i == a.size() - 1) return 1;
	if (dp[i][jump % 2] != -1) return dp[i][jump % 2];
 
	int ans = 0;
	auto pos = s.get_positions(a[i], i + 1, a.size() - 1);
	if (jump & 1) ans = rec(pos.first, jump + 1, a, s);
	else ans = rec(pos.second, jump + 1, a, s);
	return dp[i][jump % 2] = ans;
}

void	solve()
{
	int n; cin >> n;
	vi a(n);
	for(int &i : a) cin >> i;
	dp = vvi(n, vi(2, -1));
	
	segTree s(a);
	// for(int i = 0; i < n - 1; i++){
	// 	cerr << a[i] << ":: " << s.get_positions(a[i], i + 1, n - 1).first << endl;
	// 	cerr << a[i] << "::" << s.get_positions(a[i], i + 1, n - 1).second << endl;
	// }
	int ans = 1;
	for(int i = 0; i < n - 1; i++){
		int valid = rec(i, 1, a, s); 
		if (valid == 1) ans++;
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