#include <bits/stdc++.h>
using namespace std;

// link : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
	bool	get_path(TreeNode *node, TreeNode *q, vector<TreeNode *> &path)
	{
		if(!node)
			return false;
		path.push_back(node);
		if(node == q)
			return true;
		if(node->left){
			if(get_path(node->left, q, path))
				return true;
		}
		if(node->right){
			if(get_path(node->right, q, path))
				return true;
		}
		path.pop_back();
		return false;
	}

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		// map<TreeNode*, int> mp1, mp2;
		vector <TreeNode *> path1, path2;
        get_path(root, p, path1);
		get_path(root, q, path2);
		TreeNode *ans;
		int best_level = -1e9;
		for(auto &i : path1){
			auto it = find(path2.begin(), path2.end(), i);
			if(it != path2.end() && it-path2.begin() > best_level)
				ans = i, best_level = it-path2.begin();
		}
		// for(auto &m : mp1){
		// 	if(mp2.count(m.first) && m.second < min_level)
		// 		ans = m.first, min_level = m.second;
		// }
		return ans;
    }
};

//Sol2 : O(N)
class Solution2
{
public:
	TreeNode *rec(TreeNode *node, TreeNode *p, TreeNode *q){
		if(!node)		
			return nullptr;
		if(node == p)
			return p;
		if(node == q)
			return q;
		TreeNode *n1 = rec(node->left, p, q);
		TreeNode *n2 = rec(node->right, p, q);
		if(n1 == n2 && n1 == nullptr)
			return nullptr;
		if(n1 == nullptr && n2 != nullptr)
			return n2;
		if(n2 == nullptr && n1 != nullptr)
			return n1;
		return node;
	}
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		return rec(root, p, q);
	}
};