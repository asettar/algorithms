#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
using namespace std;

// prbLink : https://leetcode.com/problems/longest-string-chain/




class Solution {
	vector<vector<int>> dp;
	bool is_predecessor(string &s, string &t){
		if (s.size() != t.size() + 1)
			return 0;
		int cnt = 0;
		for(int i = 0, j = 0; i < s.size(); i++, j++){
			if (s[i] != t[j])
				j--, cnt++;
		}
		return (cnt == 1);
	}
	int rec(int i, int last, vector<string> &words){
		if (i == words.size())
			return 0;
		if (dp[i][last+1] != -1)
			return dp[i][last+1];
		int ans = rec(i + 1, last, words);
		if (last == -1 || is_predecessor(words[i], words[last]))
			ans = max(ans, 1 + rec(i + 1, i, words));
		return dp[i][last+1] = ans;
	}
public:
    int longestStrChain(vector <string>& words) {
		int n = words.size();
		dp = vector<vector<int>> (n, vector<int> (n+1, -1));
		sort(words.begin(), words.end(), [](const string &s1, const string &s2){
			return (s1.size() < s2.size());});
		return rec(0, -1, words);
    }
};

int main(){
	Solution S;
	vector<string> v = {"xbc","pcxbcf","xb","cxbc","pcxbc"};
	cout << S.longestStrChain(v);
}