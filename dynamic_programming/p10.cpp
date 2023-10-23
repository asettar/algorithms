#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

class Solution {
    int dp[50001][2];
	int rec(int i, int buy, int fee, vector<int>&prices){
		if (i == prices.size())
			return 0;
        if (dp[i][buy] != -1)
            return dp[i][buy];
		int ans = INT_MIN;
		if (buy){
			ans = max(ans, rec(i + 1, buy, fee, prices));
			ans = max(ans, -fee + prices[i] + rec(i + 1, 0, fee, prices));
		}
		else{
			ans = max(ans, rec(i + 1, 0, fee, prices));
			ans = max(ans, -prices[i] + rec(i + 1, 1, fee, prices));
		}
		return dp[i][buy] = ans;
	}
public:
    int maxProfit(vector<int>& prices, int fee) {
        memset(dp, -1, sizeof(dp));
        return rec(0, 0, fee, prices);
    }
};