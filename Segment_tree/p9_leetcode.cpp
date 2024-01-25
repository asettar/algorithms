#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

// prblink: https://leetcode.com/problems/longest-increasing-subsequence/description/
struct segTree {
	int identity = 0;
	int fn(int a, int b) {
		return max(a, b);
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

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
		vector<int> arr = nums;
		sort(arr.begin(), arr.end());
		arr.erase(unique(arr.begin(), arr.end()), arr.end());
		map<int, int> mp;
		for(int i = 0; i < arr.size(); i++){
			mp[arr[i]] = i + 1;
		}
		int mx = arr.size() + 2;
		vector<int> cnt(mx);
		segTree s(cnt);
		for(int &i : nums) {
			int nice_i = mp[i];
			// cerr << i << ' ' << nice_i << endl;
			int mx_cur_lis = s.query(0, nice_i - 1);
			s.update(nice_i, mx_cur_lis + 1);
		}
		return s.query(0, mx);
    }
};


int main(){
	Solution s;
	vector<int> a = {0,1,0,3,2,3};
	cout << s.lengthOfLIS(a) << endl;
	a = {10,9,2,5,3,7,101,18};
	cout << s.lengthOfLIS(a) << endl;
	a = {-2, -1};
	cout << s.lengthOfLIS(a) << endl;
}
