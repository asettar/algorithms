#include <bits/stdc++.h>
using namespace std;

//link : https://leetcode.com/problems/diameter-of-binary-tree/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//Solution1 : Brute force O(N^2) // calculating each time height of left and right subtree
//and keep the diameter as the sum of left and right height and return the maximum diameter for all nodes

//Solution 1 : O(N) : almost same as the previous problem approach, we keep track of the height of the left subtree and height of the right subtree
// and we take the maximum diameter after traversing all nodes
// beats 91%

class Solution {
public:
	pair<int, pair<int, int>> rec(TreeNode *node)
	{
		pair<int, pair<int, int>> res={0, {0, 0}};
		if(node->left)
		{
			pair<int, pair<int, int>> p = rec(node->left);
			res.first = max(res.first, p.first);
			res.second.first = max({res.second.first, 1 + p.second.first, 1 + p.second.second});
		}
		if(node->right){
			pair<int, pair<int, int>> p = rec(node->right);
			res.first = max(res.first, p.first);
			res.second.second = max({res.second.second, 1 + p.second.first, 1 + p.second.second});
		}
		res.first = max(res.first, res.second.first + res.second.second);
		return res;

	}

    int diameterOfBinaryTree(TreeNode* root) {
		if(!root)
			return 0;
		return rec(root).first;
    }
};

// Solution 2 : O(N) // simpler we just keep the same code for height and we update the answer

class Solution2
{
	int	rec(TreeNode *node, int &ans)
	{
		if(!node)
			return 0;
		int lh = 0, lr = 0;
		if(node->left) 
			lh = 1 + rec(node->left, ans);
		if(node->right)
			lr = 1 + rec(node->right, ans);
		ans = max(ans, lh + lr);
		return max(lh, lr);
	}

    int diameterOfBinaryTree(TreeNode* root) {
		int ans = 0;
		rec(root, ans);
		return ans;
	}
};
