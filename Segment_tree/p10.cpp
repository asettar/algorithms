#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

// prb : find the index i where the prefix_sum is >= x
 // you can do with it prefix sum and binsearch in log(n) but when there is ubdate this is not possible
 
 
 // using segTree we can do it in just (log^2(n)* Queries)

// int main() {
// 	int n; cin >> n;
// 	vector <int> a(n);
// 	for(int &i : a) cin >> i;
// 	segTree s(a);
// 	int q; cin >> q;
// 	while(q--){
// 		int x; cin >> x;
// 		int l = 0, r = n - 1, ans = -1;
// 		while(l <= r)		{
// 			int mid = (l + r) / 2;
// 			if (s.query(0, mid) >= x){
// 				ans = mid;
// 				r = mid - 1;
// 			}
// 			else l = mid + 1;
// 		}
// 		cout << ans << endl;
// 	}
// }



// you can update it in just O(log(n)) 


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
		all[i] = val;
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

	int query(int node, int l, int r, int x){
		// cerr << l << ' ' << r << ' ' << x << ": " << s[node] << endl;
		if (s[node] < x) return -1;
		if (l == r) return l;
		int mid = (l + r) / 2;
		if (s[2 * node] >= x)
			return query(2 * node, l, mid, x);
		else return query(2 * node + 1, mid + 1, r, x - s[2 * node]);
	}
};




int	main(){
	int n; cin >> n;
	vector <int> a(n);
	for(int &i : a) cin >> i;
	segTree s(a);
	int q; cin >> q;
	while(q--){
		int x; cin >> x;
		cout << s.query(1, 0, n - 1, x)	<< endl;
		return 0;
	}
}

// follow_up : sliding subbaray beauty leetcode : p11