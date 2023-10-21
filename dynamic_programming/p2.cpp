#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink: https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/


class Solution {
private :
	vector<vector<int>> dp;
	int	rec(int i, int j, string &s){
		if (i == j || i > j)
			return 0;
		if (dp[i][j] != -1)
			return dp[i][j];
		int ans = INT_MAX;
		if (s[i] == s[j])
			ans = min(ans, rec(i + 1, j - 1, s));
		else{
			ans = min(ans, 1 + rec(i + 1, j, s));
			ans = min(ans, 1 + rec(i, j - 1, s));
		}
		return ans;
	}
public :
    int minInsertions(string s) {
		int n = s.size();
		dp = vector<vector<int>> (n, vector<int>(n, -1));
		return rec(0, s.size() - 1, s);
	}
};

int main(){
	Solution S;
	string s = "leetcode";
	cout << S.minInsertions(s) << endl;
}