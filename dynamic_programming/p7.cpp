#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


// prbLink:


class Solution {
	vector<vector<int>> dp;
	bool	rec(int i, int j, string s, string p){
		if (i == s.size() && j == p.size())
			return true;
		if (j == p.size())
			return false;
		if (i == s.size())
			return (count(p.begin() + j, p.end(), '*') == p.size() - j);
		if (dp[i][j] != -1)
			return dp[i][j];
		if (s[i] == p[j] || p[j] == '?')
			return rec(i + 1, j + 1, s, p);
		bool ans = false;
		if (p[j] == '*')
		{
			for(int k = i; k <= s.size(); k++){
				ans = ans || rec(k, j + 1, s, p);
			}
		}
		return dp[i][j] = ans;
		
	}
public:
    bool isMatch(string s, string p) {
		dp = vector<vector<int>> (s.size(), vector<int>(p.size(), -1));
        return rec(0, 0, s, p);
    }
};


int main(){
	Solution s;
	cout << s.isMatch("adceb", "*a*b") << endl;
}