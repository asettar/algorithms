#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#define int long long
using namespace std;

// prblink: https://codeforces.com/contest/52/problem/C
struct segTree{
	vector<int> all;
	int n;
	vector<int> s;
	vector<int> lazy;

	int fn(int a, int b){
		return min(a, b);
	}
	segTree(vector<int> &a){
		n = a.size();
		all = a;
		s.resize(4 * n);
		lazy.resize(4 * n);
		build(1, 0, n - 1);
	}
	void	build(int node, int start, int end){
		if (start == end){
			s[node] = all[start];
			return ;
		}
		int mid = (start + end) / 2;
		build(2 * node, start, mid);
		build(2 * node + 1, mid + 1, end);
		s[node] = fn(s[2*node], s[2*node + 1]);
	}
	
	void	push_down(int node, int start, int end) {
		s[node] += lazy[node];
		if (start != end){
			lazy[2 * node] += lazy[node];
			lazy[2 * node + 1] += lazy[node];
		}
		lazy[node] = 0;
	}

	void	update(int node, int start, int end, int l, int r, int val){
		push_down(node, start, end);
		if (start > r ||  end < l) return ;
		if (start >= l && end <= r){
			lazy[node] += val;
			push_down(node, start, end);
			return ;
		}
		int mid = (start + end) / 2;
		update(2 * node, start, mid, l, r, val);
		update(2 * node + 1, mid + 1, end, l, r, val);
		s[node] = fn(s[2 * node], s[2 * node + 1]);
	}
	void	update(int l, int r, int val){
		update(1, 0, n - 1, l, r, val);
	}
	
	int query(int node, int start, int end, const int l, const int r){
		push_down(node, start, end);
		if (start > r || end < l) return 2e18;
		if (start >= l && end <= r) return s[node];
		int mid = (start + end) / 2;
		int left = query(2 * node, start, mid, l, r);
		int right = query(2 * node + 1, mid + 1, end, l, r);
		return min(left, right);
	}
	int query(int l, int r){
		return query(1, 0, n - 1, l, r);
	}
};

int32_t main(){
	int n; cin >> n;
	vector<int> a(n);
	for(int &i : a) cin >> i;
	segTree seg(a);
	int q; cin >> q; cin.ignore();
	while(q--){
		string s;
		getline(cin, s);
		stringstream ss(s);
		vector<int> nums;
		int nn;
		while (ss >> nn)
			nums.push_back(nn);
		int l = nums[0], r = nums[1], val;
		if (nums.size() == 3){
			val = nums[2];
			if (l > r){
				seg.update(l, n - 1, val);
				seg.update(0, r, val);
			}
			else seg.update(l, r, val);
		}
		else{
			if (l > r)
				cout << min(seg.query(l, n - 1), seg.query(0, r)) << endl;
			else cout << seg.query(l, r) << endl;
		}
	}
}
