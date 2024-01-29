#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

// prblink:spoj.com/problems/GIVEAWAY/cstart=20
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
  
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
template<class T> using ordered_multiset = tree<T, null_type, greater_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct segTree {
	ordered_multiset<int> identity;
	ordered_multiset<int> fn(ordered_multiset<int> &a, ordered_multiset<int> &b) {
		ordered_multiset<int> res;
		for(int i : a)
			res.insert(i);
		for(int i : b)
			res.insert(i);
		return res;
	}

	int n;
	vector<int> all;
	vector<ordered_multiset<int>> s;

	segTree(vector<int> &a) {
		n = a.size();
		s.resize(3 * n, identity);
		all = a;
		build(1, 0, n-1, 0, n-1);
	}

	void build(int node, int start, int end, const int &l, const int &r) {
		if (start > r || end < l)
			return ;
		
		if (start == end) {
			s[node].insert(all[start]);
			return ;
		}

		int mid = (start + end) / 2;
		build(2*node, start, mid, l, r);
		build(2*node+1, mid + 1, end, l, r);
		s[node] = fn(s[2*node], s[2*node+1]);
	}

	// update in just logˆ2(n)
	void update(int node, int start, int end, const int &i, const int val, const int prev_val){
		if (start == end){
			all[i] = val;
			s[node].erase(s[node].begin()); // upperbound will give itertor to prev_val
			s[node].insert(val);
			return ;
		}
		int mid = (start + end) / 2;
		if (i <= mid)
			update(2 * node, start, mid, i, val, prev_val);
		else
			update(2 * node + 1, mid + 1, end, i, val, prev_val);
		s[node].erase(s[node].upper_bound(prev_val));
		s[node].insert(val);
	}
	void update(int i, int &val) {
		update(1, 0, n - 1, i, val, all[i]);
		// all[i] = val;
	}
	
	int query(int node, int start, int end, const int &l, const int &r, const int &k) {

		if (start > r || end < l)
			return 0;

		if (start >= l && end <= r)
			return (s[node].order_of_key(k - 1)); // will give number of element greater than or equal to k
		int mid = (start + end) / 2;
		int a = query(2*node, start, mid, l, r, k);
		int b = query(2*node+1, mid+1, end, l, r, k);
		return a + b;
	}

	int query(int l, int r, const int &k) {
		return query(1, 0, n-1, l, r, k);
	}
};

int main(){
	int n; scanf("%d", &n);
	vector <int> a(n);
	for(int &i : a) scanf("%d", &i);
	segTree s(a);
	int q; scanf("%d", &q);
	int type, i, val, l, r, k;
	while(q--)	{
		scanf("%d", &type);
		if (type){
			scanf("%d%d", &i, &val);
			s.update(i - 1, val);
		}
		else {
			scanf("%d%d%d", &l, &r, &k);
			printf("%d\n", s.query(l - 1, r - 1, k));
		}
	}
}
