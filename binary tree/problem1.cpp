#include <bits/stdc++.h>
using namespace std;
// link : https://leetcode.com/problems/balanced-binary-tree/
 /**
 * Definition for a binary tree node.*/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Solution 1: Brute Force O(N^2) : We can do it easily by calculating each time the height of the
// left subtree and compare it to height right subtree, if the condition is not true we return false, if it is , we call recursively right node and left node  

//Solution 2: O(N): res.first will store our ans, res.second.first will stor our left subtree height, 
//res.second.second will store our right subtree height
// Beats 90%
class Solution {
public:
	pair<bool, pair<int, int>> rec(TreeNode *node)
	{
		pair<bool, pair<int, int>> res ={1, {0, 0}};
		if(node->left)
		{
			auto p = rec(node->left);
			res.first =  res.first && p.first;
			res.second.first += 1 + max(p.second.first, p.second.second);
		}
		if(node->right)
		{
			auto p = rec(node->right);
			res.first = res.first && p.first;
			res.second.second += 1 + max(p.second.second,p.second.first);
		}
		res.first = res.first && abs(res.second.second-res.second.first) <=1;
		return res;
	}
    bool isBalanced(TreeNode* root) {
		if(!root)
			return true;
        return rec(root).first;
    }
};

// Solution 3 : O(N) simpler(not mine) : this solution is based on the same code of height of the tree
// we just return -1 if the absolute diff between height of the left subtree and right subtree is greater than one, else we retun the height 
class Solution2 {
	int	check(TreeNode *node)
	{
		if(!node)
			return 0;
		int ans = 0;
		int left_height = 0, right_height = 0;
		if(node->left)
			left_height = 1 + check(node->left);
		if(node->right)
			right_height = 1 + check(node->right);
		if(abs(right_height - left_height) > 1)
			return -1;
		if((left_height == 0 && node->left) || (right_height == 0 && node->right))
			return -1;
		return max(left_height, right_height);
	}
    bool isBalanced(TreeNode* root) {
		return (check(root) != -1);
	}
};


