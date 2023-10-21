#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink: https://leetcode.com/problems/longest-palindromic-subsequence/

// memoisation code :
class Solution {

private :
    vector<vector<int>> dp;
	int rec(int i, int j, string &s)
	{
		if (i > j)
			return 0;
		if (i == j)
			return 1;
        if (dp[i][j] != -1)
            return dp[i][j];
		int ans = 0;
		if (s[i] == s[j])
			ans = 2 + rec(i+1, j-1, s);
		else{
			ans = rec(i+1, j, s);
			ans = max(ans, rec(i, j-1, s));
		}
		return dp[i][j] = ans;
	}
public :
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        dp = vector<vector<int>> (n, vector<int>(n, -1));
		return rec(0, n - 1, s);
    }
};

// tabulation code:

class Solution2 {
public:
    int longestPalindromeSubseq(string s) {
		int n = s.size();
		vector<vector<int>> dp(n+1, vector<int> (n+1));
		for(int i = n - 1; i >= 0; i--){
			for(int j = i; j < n; j++){
				if (s[i] == s[j])
				{
					dp[i][j] = 1;
					if (i != j)
						dp[i][j] += 1 + dp[i+1][j-1];
				} 
				else
					dp[i][j] = max(dp[i + 1][j], dp[i][j-1]);
			}
		}
		return dp[0][n - 1];
    }
};

int main(){

}