#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink: https://leetcode.com/problems/delete-operation-for-two-strings/



class Solution {
    vector<vector<int>> dp;
	int lcs(int i, int j, string word1, string &word2){
		if (i == word1.size() || j == word2.size())
			return 0;
        if (dp[i][j] != -1)
            return dp[i][j];
		int ans = 0;
		if (word1[i] == word2[j])
			ans = 1 + lcs(i + 1, j + 1, word1, word2);
		else {
			ans = lcs(i + 1, j, word1, word2);
			ans = max(ans, lcs(i, j + 1, word1, word2));
		}
		return dp[i][j] = ans;
	}
public:
    int	minDistance(string word1, string word2) {
        dp = vector <vector<int>> (word1.size(), vector<int>(word2.size(), -1));
		int lcs_len = lcs(0, 0, word1, word2);
		return word1.size() + word2.size() - 2 * lcs_len;
    }
};