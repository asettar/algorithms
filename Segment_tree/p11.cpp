#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

// prblink : https://leetcode.com/problems/sliding-subarray-beauty/
// we can solve this problem with the given constraints with just sliding window and for each subarray of lenght k, 
// we iterating over all negative numbers stored in a map since they are >= -50 to get the xth one 
// but fo higher constraints on nums[i] using segTree will solve the problem in (Onlog(n))

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
		all[i] += val;
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
	int get_index_sum(int node, int l, int r, int x){
		// cerr << l << ' ' << r << ' ' << x << ": " << s[node] << endl;
		if (s[node] < x) return -1;
		if (l == r) return l;
		int mid = (l + r) / 2;
		if (s[2 * node] >= x)
			return get_index_sum(2 * node, l, mid, x);
		else return get_index_sum(2 * node + 1, mid + 1, r, x - s[2 * node]);
	}
};

class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
		int n = nums.size();
		vector<int> ans;
		vector<int> neg;
		for(int i : nums){
			if (i < 0) neg.push_back(i);
		}
		sort(neg.begin(), neg.end());
		neg.erase(unique(neg.begin(), neg.end()), neg.end());
		map<int, int> mp, rev;
		for(int i = 0; i < neg.size(); i++) {
			mp[neg[i]] = i;
			rev[i] = neg[i];
		}
		int mx = neg.size() + 1;
		vector <int> freq(mx);
        segTree s(freq);
		for(int i = 0; i < n; i++){
			if (nums[i] < 0)
				s.update(mp[nums[i]], 1);
			if (i >= k - 1){
				int index = s.get_index_sum(1, 0, mx - 1, x);
				// cerr << index << ' ' << rev[index] << endl;
				ans.push_back(rev[index]);
				if (nums[i - k + 1] < 0)
					s.update(mp[nums[i - k + 1]], -1);
			}
		}
		return ans;
    }
};


int main(){
	Solution s;
	vector<int> a = {-3,1,2,-3,0,-3};
	vector<int> ans = s.getSubarrayBeauty(a, 2, 1);
	for(int i : ans) cout << i << ' ';
	cout << endl;
}