#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


// prblink : https://www.codechef.com/problems/MULTQ3?tab=statement
struct segTree{
	vector<int> all;
	int n;
	vector<vector<int>> s;
	vector<int> lazy;
	vector<int> cnt;

	vector<int> fn(vector<int> &a, vector<int> &b){
		vector<int> res(3);
		for(int i = 0; i < 3; i++){
			res[i] = a[i] + b[i];
		}
		return res;
	}
	
	segTree(vector<int> &a){
		n = a.size();
		all = a;
		s.resize(4 * n, vector<int> (3));
		lazy.resize(4 * n);
		cnt.resize(4 * n);
		build(1, 0, n - 1);
	}
	void	build(int node, int start, int end){
		if (start == end){
			s[node][0]++;
			return ;
		}
		int mid = (start + end) / 2;
		build(2 * node, start, mid);
		build(2 * node + 1, mid + 1, end);
		s[node] = fn(s[2*node], s[2*node + 1]);
	}
	
	void	push_down(int node, int start, int end) {
		if (!lazy[node]) return ;
		int m = lazy[node] % 3;
		vector<int> res(3);
		for(int i = 0; i < 3; i++){
			res[(i + m)%3] = s[node][i];
		}
		s[node] = res;
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
			push_down(node, start, end);
			return ;
		}
		int mid = (start + end) / 2;
		update(2 * node, start, mid, l, r);
		update(2 * node + 1, mid + 1, end, l, r);
		s[node] = fn(s[2 * node], s[2 * node + 1]);
	}

	void	update(int l, int r){
		update(1, 0, n - 1, l, r);
	}
	
	int query(int node, int start, int end, const int l, const int r){
		push_down(node, start, end);
		if (start > r || end < l) return 0;
		if (start >= l && end <= r){
			return s[node][0];
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


int main(){
	int n, q; cin >> n >> q;
	vector<int> a(n);
	segTree s(a);
	while(q--){
		int t, l, r; cin >> t >> l >> r;
		if (!t) {
			s.update(l, r);
		} else {
			cout << s.query(l, r) << endl;;
		}
	}
}
