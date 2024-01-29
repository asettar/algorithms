#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

// prblink : https://www.spoj.com/problems/MKTHNUM/
struct segTree{
	vector<vector<int>> s;
	vector<int> identity;
	vector<int> all;
	int n;
	segTree(vector<int> &a){
		n = a.size();
		all = a;
		s.resize(4 * n);
		build(1, 0, n - 1);
	}
	vector<int> fn(vector<int> &a, vector<int> &b){
		vector<int> res(a.size() + b.size());
		int i = 0, j = 0, k = 0;
		while(i < a.size() && j < b.size()){
			if (a[i] <= b[j])
				res[k++] = a[i++];
			else res[k++] = b[j++];
		}
		while(i < a.size())
			res[k++] = a[i++];
		while(j < b.size())
			res[k++] = b[j++];
		return res;
	}
	void	build(int node, int start, int end){
		if (start == end){
			s[node].push_back(all[start]);
			return ;
		}
		int mid = (start + end) / 2;
		build(2 * node, start, mid);
		build(2 * node + 1, mid + 1, end);
		s[node] = fn(s[2 * node], s[2 * node + 1]);
	}

	int count_nums(int node, int start, int end, const int l, const int r, const int num){
		if (start > r || end < l) return 0;
		if (start >= l && end <= r){
			int cnt = upper_bound(s[node].begin(), s[node].end(), num) - s[node].begin();
			return cnt;
		}
		int mid = (start + end) / 2;
		int left = count_nums(2 * node, start, mid, l, r, num);
		int right = count_nums(2 * node + 1, mid + 1, end, l, r, num);
		return left + right;
	}

	int query(int l, int r, int k){
		int start = -1e9, end = 1e9, ans;
		while (start <= end){
			int mid = (start + end) / 2;
			if (count_nums(1, 0, n - 1, l, r, mid) < k)
				start = mid + 1;
			else {
				end = mid - 1;
				ans = mid;
			}
		}
		return ans;
	}
};

int main() {
	int n, m; cin >> n >> m;
	vector<int> a(n);
	for(int &i : a) cin >> i;
	segTree s(a);
	while(m--){
		int i, j, k; cin >> i >> j >> k;
		cout << s.query(i - 1, j - 1, k) << '\n';
	}
}
