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

//prb link : https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

struct Node {
	int mn = 2e9;
	int cnt = 0;
};

vector<Node> seg;



struct segTree {
	Node identity = {(int)2e9, 0};
	Node fn(Node a, Node b){
		Node res;
		res.mn = min(a.mn, b.mn);
		res.cnt = 0;
		if (res.mn == a.mn)
			res.cnt += a.cnt;
		if (res.mn == b.mn)
			res.cnt += b.cnt;
		return res;
	}

	int n;
	vector<int> all;
	vector<Node> s;

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
			s[node] = {all[start], 1};
			return ;
		}

		int mid = (start + end) / 2;
		build(2*node, start, mid, l, r);
		build(2*node+1, mid + 1, end, l, r);
		s[node] = fn(s[2*node], s[2*node+1]);
	}

	void update(int i, int val) {
		all[i] = val;
		build(1, 0, n-1, i, i);
	}
	
	Node query(int node, int start, int end, const int l, const int r) {

		if (start > r || end < l)
			return identity;

		if (start >= l && end <= r)
			return s[node];

		int mid = (start + end) / 2;

		Node a = query(2*node, start, mid, l, r);
		Node b = query(2*node+1, mid+1, end, l, r);
		return fn(a, b);
	}
	Node query(int l, int r) {
		return query(1, 0, n-1, l, r);
	}
};

void	solve()
{
	int n, q; cin >> n >> q;
	vector<int> a(n);
	for(int &i : a) cin >> i;
	segTree s(a);
	while(q--){
		int t; cin >> t;
		if (t == 1){
			int i, val; cin >> i >> val;
			s.update(i, val);
		}
		else{
			int l, r; cin >> l >> r;
			Node res = s.query(l, r - 1);
			cout << res.mn << ' ' << res.cnt << endl;
		}
	}
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
