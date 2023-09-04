#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// prblink: https://leetcode.com/problems/maximum-xor-with-an-element-from-array/


struct Node{
	Node *bits[2];
	bool is_leaf=0;

	bool contain(int bit){
		return (bits[bit] != nullptr);
	}
	void	putnode(Node *node, int bit){
		bits[bit] = node;
	}
	Node	*getnext(int bit){
		return bits[bit];
	}
	void	setend(){
		is_leaf = 1;
	}
};

struct trie{
public:
	
	Node *root;
	trie(){
		root = new Node();
	}
	void	insert(int n){
		Node *node = root;
		for(int i=31; i>=0; i--){
			bool bit = n & (1 << i);
			if (!node->contain(bit))
				node->putnode(new Node(), bit);
			node = node->getnext(bit);
		}
		node->setend();
	}
	int	search_max(int n){
		int ans = 0;
		Node *node = root;
		for(int i=31; i>=0; i--){
			bool bit = n & (1 << i);
			if (node->contain(!bit)){
				ans |= (1 << i);
				node = node->getnext(!bit);
			}
			else{
				node = node->getnext(bit);
			}
		}
		return ans;
	}
};

bool compare(vector<int> &v1, vector<int> &v2){
	return (v1[1] < v2[1]);
}
class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
		int n = queries.size();
		vector<int> ans(n);
		trie tr;
		vector<vector<int>> arr(n);
		int i=0,flg=0;
		for(auto &v : queries){
			arr[i] = {v[0], v[1], i};
			i++;
		}
		sort(arr.begin(), arr.end(), compare);
		sort(nums.begin(), nums.end());
		i = 0;
		for(auto &v : arr){
			int x = v[0], m = v[1], pos = v[2];
			int prei = i;
			while(i < nums.size() && nums[i] <= m)
			{
				tr.insert(nums[i]);
				// cout << nums[i] << ' ' << m << ' '<<endl;
				flg = 1;
				i++;
			}
			if (!flg){
				ans[pos] = -1;
				// cout << ans[pos] << endl;
				continue;
			}
			int val = tr.search_max(x);
			ans[pos] = val;
			// cout << ans[pos] << endl;
		}
		return ans;
    }
};

int main()
{
	vector<int> nums={5,2,4,6,6,3};
	vector<vector<int>> q={{12,4},{8,1},{6,3}};
	Solution s;
	vector<int> ans = s.maximizeXor(nums, q);
	for(int i : ans)
		cout << i << ' ';
	cout << endl;
}
