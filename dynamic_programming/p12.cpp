#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
using namespace std;

// prbLink: https://leetcode.com/problems/largest-divisible-subset/


class Solution {
	vector<vector<int>> dp;
	int rec(int i, int last, vector<int> &nums){
		if (i == nums.size())
			return 0;
		if (dp[i][last] != -1)
			return dp[i][last];
		int ans = 0;
		ans = rec(i + 1, last, nums);
		if (last == 0)
			ans = max(ans, 1 + rec(i + 1, i + 1, nums));
		else if (nums[i] % nums[last-1] == 0){
			ans = max(ans, 1 + rec(i + 1, i + 1, nums));
		}
		return dp[i][last] = ans;
	}
	void build_subset(int i, int last, vector <int> &nums, vector<int> &ans){
	if (i == nums.size())
		return ;
	int choice1 = rec(i + 1, last, nums);
	int choice2 = 0;
	if (last == 0 || nums[i] % nums[last-1] == 0)
		choice2 = 1 + rec(i + 1, i+1, nums);
	if (rec(i, last, nums) == choice1)
		build_subset(i + 1, last, nums, ans);
	else{
		ans.push_back(nums[i]);
		build_subset(i+ 1, i + 1, nums, ans);
	}
} 
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
		vector<int> ans;
		int n = nums.size();
		dp = vector<vector<int>> (n, vector<int>(n + 1, -1));

		sort(nums.begin(), nums.end());
		rec(0, 0, nums);
		build_subset(0, 0, nums, ans);
		return ans;
    }
};


int main(){
	Solution s;
	vector<int> v = {4,8,10,240};
	vector<int> ans = s.largestDivisibleSubset(v);
	for(int i : ans)
		cout << i << ' ';
		
}