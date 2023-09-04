#include <bits/stdc++.h>
using namespace std;
 
// link : https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Solution 1 : using BFS Tie com : O(N * log(N))
class Solution {
public:
	struct cell
	{
		TreeNode *node;
		int r;
		int c;
	};
    vector<vector<int>> verticalTraversal(TreeNode* root)
	{
		map<int, map<int, multiset<int>>> mp;
		vector<vector<int>> ans;
		queue<cell> q;
		if(root)
			q.push({root, 0, 0});
		for(int sz=1;!q.empty(); sz=q.size())
		{
			while(sz--){
				cell cur = q.front();
				q.pop();
				mp[cur.c][cur.r].insert(cur.node->val);
				if(cur.node->left)
					q.push({cur.node->left, cur.r + 1, cur.c - 1});
				if(cur.node->right)
					q.push({cur.node->right, cur.r + 1, cur.c + 1});
			}
		}
		for(auto &p : mp){
			vector<int> sub_ans;
			for(auto &pp: p.second){
				for(const int &i : pp.second)
					sub_ans.push_back(i);
			}
			ans.push_back(sub_ans);
		}
		return ans;
	}
};
