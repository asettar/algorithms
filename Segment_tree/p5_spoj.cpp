#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
// prblink : https://www.spoj.com/problems/FREQUENT/


struct Node{
	int mx = 0;
	int var_left = 0;
	int freq_left = 0;
	int var_right = 0;
	int  freq_right = 0;
};

struct segTree {
	Node identity = {0, (int)1e9, 0, (int)1e9, 0};
	Node fn(Node a, Node b) {
		Node ret;
		if (a.var_right == b.var_left){
			int freq = a.freq_right + b.freq_left;
			if (a.var_right == a.var_left)
				a.freq_left = freq;
			if (b.var_left == b.var_right)
				b.freq_right = freq;
			ret.mx = freq;
		}
		ret.var_left = a.var_left;
		ret.freq_left = a.freq_left;
		ret.var_right = b.var_right;
		ret.freq_right = b.freq_right;
		ret.mx = max({ret.mx, a.mx, b.mx});
		ret.mx = max({ret.mx, ret.freq_left, ret.freq_right});
		return ret;
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
			s[node] = {1, all[start], 1, all[start], 1};
			// cerr << start << "|| " << s[node].mx << ' ' << s[node].var_left << ' ' << s[node].freq_left << ' '
			// 	 << s[node].var_right << ' ' << s[node].freq_right <<  '\n';
			return ;
		}

		int mid = (start + end) / 2;
		build(2*node, start, mid, l, r);
		build(2*node+1, mid + 1, end, l, r);
		s[node] = fn(s[2*node], s[2*node+1]);
		// cerr << start << ' ' << end << " || "<< s[node].mx << ' ' << s[node].var_left << ' ' << s[node].freq_left << ' '
		// 		 << s[node].var_right << ' ' << s[node].freq_right <<  '\n';
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
	int query(int l, int r) {
		return query(1, 0, n-1, l, r).mx;
	}
};

void solve(int n){
	int q;
	scanf("%lld", &q);
	vector <int> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	segTree s(a);
	for(int i = 0; i < q; i++){
		int l, r;
		scanf("%lld%lld", &l, &r);
		l--, r--;
		cout << s.query(l, r) << '\n';
	}
}

int32_t	main() {
	int n;
	while(scanf("%lld", &n) && n != 0){
		solve(n);
	}
}