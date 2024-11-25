#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <cstring>
#include <climits>
#include <sstream>
#include <iomanip>
#include <numeric>
using namespace std;

// euler tour: is a technique to use if you want to flatten the tree, each subtree will have a range {start, end}
// helpfull in queries on trees type of problems

// problem Link : https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/description/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
        vector<int> start, end;   // start and end of a subtree
        vector<int> depth;
    int countNodes(TreeNode *root) {
        if (!root) return 0;
        int ans = 1;
        if (root->left) ans += countNodes(root->left);
        if (root->right) ans += countNodes(root->right);;
        return ans;
    }
    void    eulerTour(TreeNode *root, int &ind, int depthCnt) {
        start[root->val] = ind;
        depth[ind] = depthCnt;
        if (root->left) {
            ind++;
            eulerTour(root->left, ind, depthCnt + 1);
        }
        if (root->right) {
            ind++;
            eulerTour(root->right, ind, depthCnt + 1);
        }
        end[root->val] = ind;
    }

public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        int n = countNodes(root);
        start = vector<int> (n + 1);
        end = vector<int> (n + 1);
        depth = vector<int> (n + 1);

        int ind = 1;
        eulerTour(root, ind, 0);
        vector<int> preMax(n + 1);
        vector<int> sufMax(n + 1);
        for (int i = 1; i < n; i++) preMax[i] = max(preMax[i-1], depth[i]);
        sufMax[n] = depth[n];
        for(int i = n - 1; i >= 1; i--) sufMax[i] = max(depth[i], sufMax[i+1]);
        vector<int> ans;
        for(int i : queries) {
            int l = start[i], r = end[i];
            ans.push_back(max(preMax[l-1], (r < n ? sufMax[r+1] : 0)));
        }
        return ans;
    }
};

