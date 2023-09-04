#include <bits/stdc++.h>
using namespace std;

//link : https://www.youtube.com/watch?v=KV4mRzTjlAk&list=PLgUwDviBIf0q8Hkd7bK2Bpryj2xVJk8Vk&index=25&ab_channel=takeUforward
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        queue<TreeNode*> q;
        if(root)
            q.push(root);
        for(int sz=1; !q.empty(); sz = q.size())
        {
            int n;
            while(sz--)
            {
                TreeNode *cur = q.front();
                q.pop();
                n = cur->val;
                if(cur->left)
                    q.push(cur->left);
                if(cur->right)
                    q.push(cur->right);
            }
            ans.push_back(n);
        }
        return ans; 
    }
};

// another solution (recursive)
class Solution2 {
public:
	void	rec(TreeNode *node, int level, vector<int> &ans){
		if(!node)
			return ;
		if(ans.size() == level)
			ans.push_back(node->val);
		rec(node->right, level+1, ans);
		rec(node->left, level+1, ans);
	}
    vector<int> rightSideView(TreeNode* root) {
		vector<int> ans;
		rec(root, 0, ans);
		return ans;
	}
};