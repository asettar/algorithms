#include <iostream>
#include <vector>
using namespace std;

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
		if ((int)log2(n) & 1)
			build(1, 0, n-1, 1, 0, n-1);
		else{
			cout << "h\n";
			build(1, 0, n-1, 0, 0, n-1);
		}

	}

	void build(int node, int start, int end, int Or, const int l, const int r) {
		if (start > r || end < l)
			return ;
		
		if (start == end) {
			s[node] = all[start];
			return ;
		}

		int mid = (start + end) / 2;
		build(2*node, start, mid, !Or, l, r);
		build(2*node+1, mid + 1, end, !Or, l, r);
		if (Or) s[node] = (s[2*node] | s[2*node+1]);
		else s[node] = (s[2*node] ^ s[2*node+1]);
	}

	void update(int i, int val) {
		all[i] = val;
		if ((int)log2(n) & 1)
			build(1, 0, n-1, 1, i, i);
		else 
			build(1, 0, n-1, 0, i, i);

	}
	
	int query(int node, int start, int end, int Or, const int l, const int r) {

		if (start > r || end < l)
			return identity;

		if (start >= l && end <= r)
			return s[node];

		int mid = (start + end) / 2;

		int a = query(2*node, start, mid, !Or, l, r);
		int b = query(2*node+1, mid+1, end, !Or, l, r);
		if (Or) return (a | b);
		else return (a ^ b);
	}
	int query(int l, int r) {
		if ((int)log2(n) & 1)
			return query(1, 0, n-1, 1, l, r);
		else 
			return query(1, 0, n-1, 0, l, r);
	}
};


int main(){
	int n, m; cin >> n >> m;
	n = (1 << n);
	vector<int> a(n);
	for(int &i : a) cin >> i;
	segTree s(a);
	cout << s.s[1] << endl;
	while(m--){
		int i, val;
		cin >> i >> val;
		i--;
		s.update(i, val);
		cout << s.query(0, n - 1) << endl;
	}
}