#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

class Solution {
	int rec(int i, int buy, int left, vector<int> &prices){
		if (i == prices.size() || !left)
			return 0;
		int ans = INT_MIN;
		if (buy){
			ans = max(ans, rec(i + 1, 1, left, prices));
			ans = max(ans, prices[i] + rec(i + 1, 0, left - 1, prices));
		}
		else{
			ans = max(ans, rec(i + 1, 0, left, prices));
			ans = max(ans, - prices[i] + rec(i + 1, 1, left, prices));
		}
		return ans;
	}
public:
    int maxProfit(vector<int>& prices) {
		const int n = prices.size();
		int dp[n + 1][2][3];
		memset(dp, -1, sizeof(dp));
        return rec(0, 0, 2, prices);
    }
};
