#include <bits/stdc++.h>
using namespace std;

//link : https://www.youtube.com/watch?v=0FtVY6I4pB8&list=PLgUwDviBIf0q8Hkd7bK2Bpryj2xVJk8Vk&index=24&ab_channel=takeUforward
// bottom view of a binary treee inorder fro left to right

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// same approach with previous one
class Solution
{
public:
	struct cell
	{
		TreeNode *node;
		int r;
		int c;
	};
	vector<int> bot_view(TreeNode *root)
	{
		map<int, int> mp;   // first = col, second = bottom node value in that col
		vector<int> ans;
		queue<cell> q;
		if(root)
			q.push({root, 0, 0}), mp[0] = root->val;
		for(int sz=1;!q.empty(); sz=q.size())
		{
			while(sz--){
				cell cur = q.front();
				q.pop();
				mp[cur.c] = cur.node->val;
				if(cur.node->left)
					q.push({cur.node->left, cur.r + 1, cur.c - 1});
				if(cur.node->right)
					q.push({cur.node->right, cur.r + 1, cur.c + 1});
			}
		}
		for(auto &p : mp){
			ans.push_back(p.second);
		}
		return ans;
	}
};

