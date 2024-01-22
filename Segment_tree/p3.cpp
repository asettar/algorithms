#include <iostream>
#include <vector>
using namespace std;
#define int long long
#define double long double
#define vi vector<int>
#define all(x) x.begin(), x.end()
#define	rall(x) x.rbegin(), x.rend()
#define endl '\n'
const int mod = 1e9+7;
const int maxn = 1e5 + 10;

// prblink : https://www.spoj.com/problems/INVCNT/

//usefull trick : to get the number of elements that are gretaer or lesser than a number in log(n)
				  // you can use either ordered_set or segment tree(using freq array)

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
};



void	solve(){
	int n; cin >> n;
	vector<int> a(n);
	for(int &i : a) cin >> i;
	vector<int> freq(2e5 + 1);
	segTree s(freq);
	int ans = 0;
	for(int i : a) {
		ans += s.query(i + 1, 2e5);
		freq[i]++;
		s.update(i, freq[i]);
	}
	cout << ans << endl;
}

int32_t	main() {
	int t; cin >> t;
	while(t--) solve();
	
}