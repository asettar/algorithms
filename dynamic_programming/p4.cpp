#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink: https://leetcode.com/problems/shortest-common-supersequence/description/
   

class Solution {
	vector<vector<int>> dp;
	string lcs_s;
	int lcs(int i, int j, string &s1, string &s2){
		if (i == s1.size() || j == s2.size())
			return 0;
        if (dp[i][j] != -1)
            return dp[i][j];
		int ans = 0;
		if (s1[i] == s2[j])
			ans = 1 + lcs(i + 1, j + 1, s1, s2);
		else {
			ans = lcs(i + 1, j, s1, s2);
			ans = max(ans, lcs(i, j + 1, s1, s2));
		}
		return dp[i][j] = ans;
	}
	void	build_lcs(int i, int j, string &s1, string &s2)
	{
		if (i == s1.size() || j == s2.size())
			return ;
		if (s1[i] == s2[j])
		{
			lcs_s += s1[i];
			build_lcs(i + 1, j + 1, s1, s2);
		}
		else {
			if (dp[i][j] == lcs(i + 1, j, s1, s2))
				build_lcs(i + 1, j, s1, s2);
			else build_lcs(i, j + 1, s1, s2);
		}
	}

public :
    string shortestCommonSupersequence(string s1, string s2) {
		dp = vector <vector<int>> (s1.size(), vector<int> (s2.size(), -1));
		lcs(0, 0, s1, s2);
		build_lcs(0, 0, s1, s2);
		// cout << lcs_s << endl;
		string ans;
		int i = 0, j = 0, k = 0;
		while (i < s1.size() || j < s2.size())
		{	
			if (k >= lcs_s.size()){
				if (i < s1.size())
					ans += s1[i++];
				if (j < s2.size())
					ans += s2[j++];
			}
			else{
				while(s1[i] != lcs_s[k])
					ans += s1[i++];
				while(s2[j] != lcs_s[k])
					ans += s2[j++];
				ans += lcs_s[k++];
				i++, j++;
			}
		}
		
		return ans;
    }
};



int main() {
	Solution s;
	cout << s.shortestCommonSupersequence("bbbaaaba", "bbababbb") << endl;
}

