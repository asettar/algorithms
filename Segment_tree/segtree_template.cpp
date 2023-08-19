#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define vi vector<int>
#define all(x) x.begin(), x.end()
#define	rall(x) x.rbegin(), x.rend()
#define endl '\n'
const int mod = 1e9+7;
const int maxn = 1e5 + 10;
 
class SegTree
{
	vector<int> seg;
public :
	SegTree(int n){
		seg.resize(4 * n + 1);
	}
	void	build(int ind, int low, int high, vector<int> &arr){
		if (low == high)
		{
			seg[ind] = arr[low];
			return ;
		}
		int mid=(low+high)/2;
		build(2*ind +1, low, mid, arr);
		build(2*ind +2, mid + 1, high, arr);
		seg[ind] = min(seg[2*ind + 1], seg[2*ind +2]);
	}
	int query(int ind, int low, int high, int l, int r) {
		if (high < l || r < low)
		return INT_MAX; 
		if (l >= low && r <= high)
			return seg[ind];
		int mid = (low + high) / 2;
		int left = query(2 * ind + 1, low, mid, l, r);
		int right = query(2 * ind + 2, mid + 1, high, l ,r);
		return min(left, right);
	}
	void	update(int ind, int low, int high, int i, int val) {
		if (low == high)
		{
			seg[ind] = val;
			return ;
		}
		int mid = (low + high) / 2;
		if (i <= mid)
			update(2*ind+1, low, mid, i, val);
		else
			update(2 * ind +2, mid+1, high, i, val);
		seg[ind] = min(seg[2 * ind+1], seg[2*ind+2]);
	}
};

void	solve()
{
	int n;
	SegTree s(n);
}
 
int32_t	main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	cin >> t;
	while(t--)
		solve();
}