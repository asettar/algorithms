#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// prbLink: https://leetcode.com/problems/distinct-subsequences/


class Solution {
	vector<vector<int>> dp;
	int rec(int i, int j, string &s, string &t){
		if (j == t.size())
			return 1;
		if (i >= s.size())
			return 0;
		if (dp[i][j] != -1)
			return dp[i][j];
		int ans = 0;
		if (s[i] == t[j])
			ans += rec(i + 1, j + 1, s, t);
		ans += rec(i + 1, j, s, t);
		return dp[i][j] = ans;
	}
public :
    int numDistinct(string s, string t) {
		dp = vector<vector<int>> (s.size(), vector<int>(t.size(), -1));
		return rec(0, 0, s, t);
    }
};

int	main() {
	Solution s;
	cout << s.numDistinct("babgbag", "bag") << endl;
}
