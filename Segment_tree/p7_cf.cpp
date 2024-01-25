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

//prblink: https://codeforces.com/contest/61/problem/E
// sol : iterate over j and multply (count of left > a[j]) * (count of right < a[j])
struct segTree {
	int identity = 0;
	int fn(int a, int b) {
		return a + b;
	}

	int n;
	vector<int> all;
	vector<int> s;

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
			s[node] = all[start];
			return ;
		}

		int mid = (start + end) / 2;
		build(2*node, start, mid, l, r);
		build(2*node+1, mid + 1, end, l, r);
		s[node] = fn(s[2*node], s[2*node+1]);
	}

	void update(int i, int val) {
		all[i] += val;
		build(1, 0, n-1, i, i);
	}
	
	int query(int node, int start, int end, const int l, const int r) {

		if (start > r || end < l)
			return identity;

		if (start >= l && end <= r)
			return s[node];

		int mid = (start + end) / 2;

		int a = query(2*node, start, mid, l, r);
		int b = query(2*node+1, mid+1, end, l, r);
		return fn(a, b);
	}
	int query(int l, int r) {
		return query(1, 0, n-1, l, r);
	}
};

void	solve()
{
	int n; cin >> n;
	vector <int> a(n);
	for(int &i : a) cin >> i;
	vector<int> b = a;
	sort(all(b));
	b.erase(unique(all(b)), b.end());
	map<int, int> mp;
	for(int i = 0; i < b.size(); i++)
		mp[b[i]] = i + 1;
	int mx = b.size() + 3;
	vector<int> freq(mx);
	segTree left(freq);
	segTree right(freq);
	for(int i : a)
		right.update(mp[i], 1);
	int ans = 0;
	for(int i = 0; i < n; i++){
		a[i] = mp[a[i]];
		int cnt_greater_left = left.query(a[i] + 1, mx);
		int cnt_smaller_right = right.query(0, a[i] - 1);
		ans += cnt_greater_left * cnt_smaller_right;
		left.update(a[i], 1);
		right.update(a[i], -1);
	}
	cout << ans << endl;
}
 
int32_t	main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	// cin >> t;
	while (t--)
		solve();
}
