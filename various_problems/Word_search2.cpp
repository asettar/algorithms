#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
using namespace std;


// prblink : https://leetcode.com/problems/word-search-ii/

class trie {

public :
	vector<trie *> links;
	int end;
	trie(){
		end = 0;
		links = vector<trie *> (26);
	}
	bool search(string &word){
		trie *node = this;
		for(char c : word){
			if (!node->links[c - 'a']) return 0;
			node = node->links[c - 'a'];
		}
		return 1;
	}
};

int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, 1, -1};

class Solution {
void	dfs(int i, int j, vector<vector<bool>> &vis, string &s, trie *node, vector<vector<char>>& board) {
	// cout << i << ' ' << j << ' '  << s << ' ' << board[i][j] << endl;
	vis[i][j] = 1;
	char c = board[i][j];
	s += c;
	// cout << s << endl;
	if (node->links[c - 'a'] == nullptr)
		node->links[c - 'a'] = new trie();
     if (s.size() >= 10){
        s.pop_back();
        vis[i][j] = 0;
        return ;
    }
	for(int k = 0; k < 4; k++){
		int ni = i + di[k], nj = j + dj[k];
		if (ni < 0 || nj < 0 || ni >= vis.size() || nj >= vis[0].size() || vis[ni][nj]) continue;
		dfs(ni, nj, vis, s, node->links[c - 'a'], board);
	}
	vis[i][j] = 0;
	s.pop_back();
}

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		trie *node = new trie();
        int n = board.size(), m = board[0].size();
		vector<string> ans;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				vector<vector<bool>> vis(n, vector<bool>(m));
				string s = "";
				dfs(i, j, vis, s, node, board);
			}
		}
		for(string s : words){
			if (node->search(s)) ans.push_back(s);
			// cout << s << ' '<< node->search(s) << endl;
		}
		return ans;
    }
};




int main(){
	vector<vector<char>> b = {{'o','a','a','n'},{'e','t','a','e'}, {'i','h','k','r'},{'i','f','l','v'}};
	vector<string> words = {"oath","pea","eat","rain"};
	Solution s;
	vector<string> ans = s.findWords(b, words);
	for(string s : ans) cout << s << ' ';
}
