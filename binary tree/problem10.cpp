#include <bits/stdc++.h>
using namespace std;

// link : https://www.interviewbit.com/problems/path-to-given-node/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//sol1 :O(N)
vector<int> get_path(TreeNode *root, int target)
{
	vector<int> ans;
	vector<int> par(1e5+1);
	queue<TreeNode *> q;
	q.push(root);
	par[root->val] = root->val;
	while(!q.empty()){
		TreeNode *cur = q.front();
		q.pop();
		if(cur->val == target){->val);
		if(rec(node->right, target, path))
			return true;
		path.pop_back();
	}
	return false;
}

vector<int> get_path_2(TreeNode *root, int target)
{
	vector<int> path{root->val};

	rec(root, target, path);
	return path;
			int value = cur->val;
			while(par[value] != value){
				ans.push_back(value);
				value = par[value];
			}
			ans.push_back(value);
		if(cur->left){
			q.push(cur->left);
			par[cur->left->val] = cur->val;
		}
		if(cur->right){
			q.push(cur->right);
			par[cur->right->val] = cur->val;
		}
	}
	return ans;
}

// Solution2:O(N)
bool	rec(TreeNode *node, int target, vector<int> &path){
	if(node->val == target)
		return true;
	if(node->left){
		path.push_back(node->left->val);
		if(rec(node->left, target, path))
			return true;
		path.pop_back();
	}
	if(node->right){
		path.push_back(node->right);
	}
}