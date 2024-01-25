#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long
// prblink : https://www.spoj.com/problems/KGSS/

struct Node{
	int mx1 = 0, mx2 = 0;
};

struct segTree {
	Node identity = {0, 0};
	Node fn(Node a, Node b) {
		Node ret;
		vector<int> values;
		values.push_back(a.mx2);
		values.push_back(a.mx1);
		values.push_back(b.mx1);
		values.push_back(b.mx2);
		sort(values.rbegin(), values.rend());
		ret.mx1 = values[0];
		ret.mx2 = values[1];
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
			s[node] = {all[start], 0};
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
	int query(int l, int r) {
		Node res = query(1, 0, n-1, l, r);
		return (res.mx1  + res.mx2);
	}
};


int32_t	main() {
	int n; cin >> n;
	vector<int> a(n);
	for(int &i : a) cin >> i;
	segTree s(a);
	// cerr << s.s[1].mx1 << ' ' << s.s[1].mx2 << endl;
	int q; cin >> q;
	while(q--){
		char c; cin >> c;
		if (c == 'U'){
			int i, val; cin >> i >> val;
			i--;
			s.update(i, val);
		}
		else {
			int l, r; cin >> l >> r;
			l--, r--;
			cout << s.query(l, r) << endl;
		}
	}

}