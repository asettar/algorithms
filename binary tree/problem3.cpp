#include <bits/stdc++.h>
using namespace std;

//link : https://leetcode.com/problems/same-tree/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Simple problem O(N) beats 100%
class Solution {
public:
	bool	rec(TreeNode *p, TreeNode *q)
	{
		if(!p && !q)
			return true;
		else if((!p && q) || (!q && p) || (p->val != q->val))
			return false;
		bool ans = rec(p->left, q->left);
		if(!ans)
			return false;
		return rec(p->right, q->right);
	}
    bool isSameTree(TreeNode* p, TreeNode* q) {
       return rec(p, q);
    }
};

