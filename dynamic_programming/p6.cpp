#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink: https://leetcode.com/problems/edit-distance/

class Solution {
    vector<vector<int>> dp;
    int rec(int i, int j, string &s1, string &s2){
		if (i == s1.size())
			return s2.size() - j;
		else if (j == s2.size())
			return s1.size() - i;
        if (dp[i][j] != -1)
            return dp[i][j];
		int c1, c2, c3, c4;
		c1 = c2 = c3 = c4 = INT_MAX;
		if (s1[i] == s2[j])
			c1 = rec(i+1, j+1, s1, s2);
		else{
			c2 = 1 + rec(i+1, j+1, s1, s2);        // replace
			c3 = 1 + rec(i+1, j, s1, s2);         // insert s1[i]
			c4 = 1 + rec(i, j+1, s1, s2);			// insert s2[j]
		}
		int ans = min(c1, c2);
		ans = min({ans, c3, c4});
		return dp[i][j] = ans;
    }
public:
    int minDistance(string word1, string word2) {
        dp = vector<vector<int>>(word1.size(), vector<int>(word2.size(), -1));

        return rec(0, 0, word1, word2);
    }
};


int	main() {

}
