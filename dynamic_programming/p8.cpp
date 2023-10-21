#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

class Solution {
	int rec(int i, vector<int> &prices){
		if (i == prices.size())
			return 0;
		int ans = 0;
		ans = rec(i + 1, prices);
		for(int j = i + 1; j < prices.size(); j++){
			if (prices[j] > prices[i])
				ans = max(ans, prices[j] - prices[i] + rec(j + 1, prices));
		}
		return ans;
	}
	
public:
    int maxProfit(vector<int>& prices) {
		return rec(0, prices);
    }
};

