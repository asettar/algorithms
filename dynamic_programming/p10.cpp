#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

class Solution {
	int rec(int i, int buy, int fee, vector<int>&prices){
		if (i == prices.size())
			return 0;
		int ans = INT_MIN;
		if (buy){
			ans = max(ans, rec(i + 1, buy, fee, prices));
			ans = max(ans, -fee + prices[i] + rec(i + 1, 0, buy, prices));
		}
		else{
			ans = max(ans, rec(i + 1, buy, fee, prices));
			ans = max(ans, -prices[i] + rec(i + 1, 1, fee, prices));
		}
		return ans;
	}
public:
    int maxProfit(vector<int>& prices, int fee) {
        return rec(0, 0, fee, prices);
    }
};