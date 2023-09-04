#include <bits/stdc++.h>
using namespace std;

// boundary traversal in clockwise 
// link : https://www.youtube.com/watch?v=0ca1nvR0be4&list=PLJ_vPQ_vraNz90tiB1HNgUWjivW07RcXC&index=17&ab_channel=takeUforward 

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
	bool	is_leaf(TreeNode *node){
		return (!node ->right && !node->left);
	}

	void	add_left_boundary(TreeNode *node, vector<int> &ans)
	{
		if(!node)
			return ;
		ans.push_back(node->val);
		if(node->left && !is_leaf(node->left))
			add_left_boundary(node->left, ans);
		else if(node->right && !is_leaf(node->right))
			add_left_boundary(node->right, ans);
	}

	void	add_leaves(TreeNode *node, vector<int> &ans, TreeNode *root)
	{
		if(!node)
			return ;
		if(is_leaf(node) && node != root)
			ans.push_back(node->val);
		if(node->left)
			add_leaves(node->left, ans, root);
		if(node->right)
			add_leaves(node->right, ans, root);
	}

	void	add_right_boundary_reverse(TreeNode *node, vector<int> &ans, TreeNode *root)
	{
		if(!node)
			return ;
		if (node->right && !is_leaf(node->right))
			add_right_boundary_reverse(node->right, ans, root);
		else if(node->left && !is_leaf(node->left))
			add_right_boundary_reverse(node->right, ans, root);
		if(node != root)
			ans.push_back(node->val);
	}

	vector<int>	boundary_traversal(TreeNode *root)
	{
		vector<int> ans;
		add_left_boundary(root, ans);
		add_leaves(root, ans, root);
		add_right_boundary_reverse(root, ans, root);
		return ans;
	}
};
