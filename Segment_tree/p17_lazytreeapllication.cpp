#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


// problem : given an array one ones and zeros and queries
	// query1 :   1 l r (print how many ones between l and r) 
	// query2 :   2 l r (flip ones to zeors and zeros to ones in the range l, r)
struct segTree{
	vector<int> all;
	int n;
	vector<int> s;
	vector<int> lazy;
	vector<int> cnt;

	int fn(int a, int b){
		return a + b;
	}
	segTree(vector<int> &a){
		n = a.size();
		all = a;
		s.resize(4 * n);
		lazy.resize(4 * n);
		cnt.resize(4 * n); // how many time I did an update
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
		cnt[node] += lazy[node];
		if (start != end){
			lazy[2 * node] += lazy[node];
			lazy[2 * node + 1] += lazy[node];
		}
		lazy[node] = 0;
	}

	void	update(int node, int start, int end, int l, int r){
		push_down(node, start, end);
		if (start > r ||  end < l) return ;
		if (start >= l && end <= r){
			lazy[node]++;
			// cerr << "|| " << start << ' ' << end << ":: " << lazy[node] << " :: ";
			push_down(node, start, end);
			return ;
		}
		int mid = (start + end) / 2;
		update(2 * node, start, mid, l, r);
		update(2 * node + 1, mid + 1, end, l, r);
	}
	void	update(int l, int r){
		update(1, 0, n - 1, l, r);
	}
	
	int query(int node, int start, int end, const int l, const int r){
		push_down(node, start, end);
		if (start > r || end < l) return 0;
		if (start >= l && end <= r) {
			if (cnt[node] & 1) return (end - start + 1 - s[node]);
			return s[node];
		}
		int mid = (start + end) / 2;
		int left = query(2 * node, start, mid, l, r);
		int right = query(2 * node + 1, mid + 1, end, l, r);
		return left + right;
	}
	int query(int l, int r){
		return query(1, 0, n - 1, l, r);
	}
};

int main() { 
	int n, q; cin >> n >> q; 
	vector<int> a(n);
	for(int &i : a) cin >> i;
	segTree s(a);
	while(q--){
		int type, l, r; cin >> type >> l >> r;
		l--, r--;
		if (type == 1){
			cout << s.query(l, r) << endl;
		}
		else s.update(l, r);
	}
}


// 6
// 10
// 1 0 0 1 1 1