#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>
using namespace std;


// brute force : O(n ^ 2)
	// class Solution {
	// public :
	//     int minOperations(vector<int>& nums) {
	//         int n = nums.size(), ans = 2e9;
	// 		int ones = count(nums.begin(), nums.end(), 1);
	// 		if (ones) return n - ones;
	// 		for(int i = 0; i < n - 1; i++) {
	// 			int gd = nums[i];
	// 			for(int j = i + 1, cnt = 0; j < n; j++, cnt++){
	// 				gd = gcd(gd, nums[j]);
	// 				if (gd == 1){
	// 					ans = min(ans, n + cnt - 1);
	// 					break;
	// 				}
	// 			}
	// 		}
	// 		return (ans == 2e9 ? -1 : ans);
	//     }
	// };


// using segTree and binary search in O(n log (n)) 

struct segTree {
	int identity = 0;
	int fn(int a, int b) {
		return gcd(a, b);
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
public :
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = 2e9;
		int ones = count(nums.begin(), nums.end(), 1);
		if (ones) return n - ones;

		segTree s(nums);
		for(int i = 0; i < n; i++){
			int l = i + 1, r = n - 1, cnt = -1;
			while(l <= r) {
				int mid = (l + r) / 2;
				if (s.query(i, mid) == 1){
					cnt = mid - i;
					r = mid - 1;
				}	
				else l = mid + 1;
			}
			if (cnt != -1) ans = min(ans, n - 1 + cnt);
		}
		return (ans == 2e9 ? -1 : ans);
    }
};

int	main() {

}
