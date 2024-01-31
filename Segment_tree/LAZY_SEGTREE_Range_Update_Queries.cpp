#include <iostream>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;

// when updating a range we have a left and right,
// when we coincide with a range that is fully insinde our (l, r) we stop

// update the node when you visited it, propagted down the update 

// range update (l, r) + val: 
	// traverse the seg tree
	//update prev remaining update if there is 
	// check if the node completely overlap with (l, r)
		// -update the node
		// -lazy propagate to children if it has and return  (lazy[2*ind]+=val, lazy[2*ind+2]+=val)

	// check if the node partially overlap
		// -go left , go right
	// no overlap 
		// -return (stop the traverse)
// range query  : check if node need update other are just similar to noraml segTree


// prblink : https://cses.fi/problemset/task/1651/
struct segTree{
	vector<int> all;
	int n;
	vector<int> s;
	vector<int> lazy;

	int fn(int a, int b){
		return a + b;
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
		s[node] += lazy[node] * (end - start + 1);
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
	}
	void	update(int l, int r, int val){
		update(1, 0, n - 1, l, r, val);
	}
	
	int query(int node, int start, int end, const int l, const int r){
		push_down(node, start, end);
		if (start > r || end < l) return 0;
		if (start >= l && end <= r) return s[node];
		int mid = (start + end) / 2;
		int left = query(2 * node, start, mid, l, r);
		int right = query(2 * node + 1, mid + 1, end, l, r);
		return left + right;
	}
	int query(int l, int r){
		return query(1, 0, n - 1, l, r);
	}
};


int32_t main(){
	int n, q; cin >> n >> q;
	vector <int> a(n);
	for(int &i : a) cin >> i;
	segTree s(a);
	while(q--){
		int type; cin >> type;
		if (type == 1){
			int a, b, u; cin >> a >> b >> u;
			s.update(a - 1, b - 1, u);
		}
		else {
			int k; cin >> k;
			cout << s.query(k - 1, k - 1) << endl;
		}
	}

}