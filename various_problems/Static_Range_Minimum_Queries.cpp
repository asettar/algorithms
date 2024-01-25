#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// prb link : https://cses.fi/problemset/result/8287953/

vector<int> seg;
void	build(int ind, int l, int r, vector<int> &a){
	if (l == r){
		seg[ind] = a[l];
		return ;
	}
	int mid = l + (r - l) / 2;
	build(2 * ind + 1, l, mid, a);
	build(2 * ind + 2, mid + 1, r, a);
	seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
}

int	query(int ind, int start, int end, const int l, const int r) {
	if (start > r || end < l) return 2e9;
	if (start >= l &&  end <= r) return seg[ind];

	int mid = start + (end - start) / 2; 
	int left = query(2 * ind + 1, start, mid, l, r);
	int right = query(2 * ind + 2, mid + 1, end, l, r);
	return min(left, right);
}

int	main() {
	int n, q ; cin >> n >> q;
	vector<int> a(n);
	for(int &i : a) cin >> i;
	seg.resize(4 * n);
	build(0, 0, n - 1, a);
	while(q--){
		int l, r; cin >> l >> r;
		cout << query(0, 0, n - 1, l - 1, r - 1) << endl;
	}
}
