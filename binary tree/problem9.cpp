#include <bits/stdc++.h>
using namespace std;

// link : https://leetcode.com/problems/symmetric-tree/
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
    bool isSymmetric(TreeNode* root) {
        queue<pair<TreeNode *, int>> q;
		if(root)
			q.push({root, 0});
		for(int sz=1, l=1; !q.empty(); sz=q.size(),l++){
			vector<pair<int, int>> level;
			while(sz--){
				auto cur = q.front();
				q.pop();
				level.push_back({cur.first->val, cur.second});
				if(cur.first->left)
					q.push({cur.first->left, cur.second-1});
				if(cur.first->right)
					q.push({cur.first->right, cur.second+1});
			}
			int n = level.size();
			if(n&1 && l!=1)
				return false;
			for(int i=0; i<n/2; i++){
				if(level[i].first != level[n-1-i].first || level[n-1-i].second+level[i].second != 0)
					return false;
			}
		}
		return true;
    }
};

// solution 2 :
class Solution2 {
public:
	bool rec(TreeNode*left, TreeNode* right){
		if(left == right && left == nullptr)
			return true;
		if(left->val != right->val)
			return false;
		bool ans = rec(left->left, right->right);
		if(!ans)
			return false;
		return rec(left->right, right->left);
	}
    bool isSymmetric(TreeNode* root) {
		if(!root)
			return false;
		return rec(root->left, root->right);
	}
};