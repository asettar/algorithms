#include <iostream>
#include <vector>
using namespace std;

// prblink : https://codeforces.com/contest/380/problem/C
int n;
string s;
struct Node{
	int open, close, ans;
};

vector<Node> seg;

Node	merge(Node &a, Node &b){
	Node ret;
	ret.ans = a.ans + b.ans;
	int mn = min(a.open, b.close);
	ret.ans += mn;
	ret.open = a.open + b.open - mn;
	ret.close = a.close + b.close - mn;
	return ret;
}

void	build(int si = 0, int ss = 0, int se = n-1){
	if (ss == se){
		seg[si] = {s[ss] == '(' , s[ss] == ')', 0};
		return;
	}
	int mid = (ss+se) / 2;
	build(2*si+1, ss, mid);
	build(2*si+2, mid+1, se);
	seg[si] = merge(seg[2*si+1], seg[2*si+2]);
}

Node	query(int l, int r, int si = 0, int ss = 0, int se = n-1){
	if (se < l || ss > r){
		return {0,0,0};
	}
	if (ss >= l && se <= r)
		return seg[si];
	int	mid = (ss + se)/2;
	Node left = query(l, r, 2*si + 1, ss, mid);
	Node right = query(l, r, 2*si + 2, mid+1, se);
	return merge(left, right);
}

void	solve()
{
	cin >> s;
	n = s.size();
	seg.resize(4 * n, {0, 0, 0});
	build();
	int m;
	cin >> m;
	while(m--) {
		int l, r;
		cin >> l >> r;
		l--, r--;
		cout << query(l, r).ans * 2 << endl;
	}
}
 
int32_t	main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	// cin >> t;
	while(t--)
		solve();
}