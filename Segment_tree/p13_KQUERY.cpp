#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>
using namespace std;

// merge_sort_tree : 

	// Power we lost with normal segment tree : 
		// -count of elemts greater (or smaller than x)
		// -first element greater or smaller than x (we can do it with bin search but only if start index is = 0)
		// -sum of all elements greater or smaller than x
	// we can do this type of things with merge sort tree


// prblink: https://www.spoj.com/problems/KQUERY/

struct segTree {
	vector<int> identity = {};
	vector<int> fn(vector<int> &a, vector<int> &b) {
		vector<int> res(a.size() + b.size());
		int i = 0, j = 0, k = 0;
		while (i < a.size() && j < b.size()){
			if (a[i] < b[j])
				res[k++] = a[i++];
			else res[k++] = b[j++];
		}
		while(i < a.size())
			res[k++] = a[i++];
		while(j < b.size())
			res[k++] = b[j++];
		return res;
	}

	int n;
	vector<int> all;
	vector<vector<int>> s;

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
			s[node] = {all[start]};
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
	int	query(int node, int start, int end, const int l, const int r, const int k) {
		if (start > r || end < l) return 0;
		if (start >= l && end <= r){
			int index = upper_bound(s[node].begin(), s[node].end(), k) - s[node].begin();
			int sz = s[node].size();
			return sz - index;
		}
		int mid = (start + end) / 2;
		int left = query(2 * node, start, mid, l, r, k);
		int right = query(2 * node + 1, mid + 1, end, l, r, k);
		return (left + right);
	}
	
	int query(int l, int r, int k){
		return query(1, 0, n-1, l, r, k);

	}
};

int	main() {
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	segTree s(a);
	// for(int i : s.s[1]) cout << i ;
	// cout << endl;
	// for(int i : s.s[2]) cout << i ;
	// cout << endl;
	// for(int i : s.s[3]) cout << i ;
	// cout << endl;
	int q; cin >> q;
	while(q--){
		int l, r, k; scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", s.query(l - 1, r - 1, k));
	}
}
