#include <iostream>
#include <set>
using namespace std;

// prblink:https://practice.geeksforgeeks.org/problems/a512e4b2e812b6df2159b19cc7090ffc1ab056dd/1?utm_source=geeksforgeeks&utm_medium=article_practice_tab&utm_campaign=article_practice_tab
//brute force O(N^3)
// using prefixrray O(N^2)
// using trie : O(N)

struct Node{
	Node *bits[2];
	bool is_leaf=0;

	bool contain(Node *node, int bit){
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
			if (!node->contain(node, bit))
				node->putnode(new Node(), bit);
			node = node->getnext(bit);
		}
		node->setend();
	}
	int	search_opp_bits(int n){
		int ans = 0;
		Node *node = root;
		for(int i=31; i>=0 ;i--){
			bool bit = n & (1 << i);
			if (node->contain(node, !bit)){
				node = node->getnext(!bit);
				ans |= (1 << i);
			}
			else{
				node = node->getnext(bit);
			}
			// cout << n << ' ' << ' ' << bit << ' '<< i << ' ' << ans << endl;
		}
		return ans;
	}
};


class Solution{   
public:
    int maxSubarrayXOR(int N, int arr[]){
		trie tr;
		int ans = arr[0], xr = arr[0];
		tr.insert(arr[0]);
		for(int i=1; i<N; i++){
			xr = xr ^ arr[i];
			ans = max({ans, xr, tr.search_opp_bits(xr)});
			tr.insert(xr);
		}
		return ans;
    }
};

int main()
{
	Solution s;
	int arr[4]={1,2,3,4};
	cout << s.maxSubarrayXOR(4, arr) << endl;
}
