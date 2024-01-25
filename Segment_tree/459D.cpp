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

// f(l, r, x) = the number of elements between l and r equal to x
// find number of pairs such that   cnt_left_equal_ai > cnt_right_equal aj

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
	int	n; cin >> n;
	vector<int> a(n);
	for(int &i : a) cin >> i;
	vector<int> cnt(n + 2);
	segTree s(cnt);
	map<int, int> f1, f2;
	vector<int> left, right;
	for(int i = 0; i < n; i++) {
		f1[a[i]]++;
		left.push_back(f1[a[i]]);
	}
	for(int i = n - 1; i >= 0; i--){
		f2[a[i]]++;
		right.push_back(f2[a[i]]);
	}
	reverse(all(right));
	s.update(1, 1);
	// for(int i : left) cerr << i << ' ';
	// cerr << endl;
	// for(int i : right) cerr << i << ' ';
	// cerr << endl;
	int ans = 0;
	for(int i = 1; i < n; i++){
		int start = right[i] + 1;
		ans += s.query(start, n);
		s.update(left[i], 1);
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