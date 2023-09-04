#include <iostream>
using namespace std;

//prblinkhttps://practice.geeksforgeeks.org/problems/minimum-xor-value-pair/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article

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
	int	search_same_bits(int n){
		int ans = 0;
		Node *node = root;
		for(int i=31; i>=0 ;i--){
			bool bit = n & (1 << i);
			if (node->contain(node, bit)){
				node = node->getnext(bit);
			}
			else{
				node = node->getnext(!bit);
				ans |= (1 << i);
			}
			// cout << n << ' ' << ' ' << bit << ' '<< i << ' ' << ans << endl;
		}
		return ans;
	}

};

class Solution{   
public:
    int minxorpair(int N, int arr[]){
		int ans = 2e9;
		trie tr;
        for(int i=0 ;i<N; i++){
			if (!i)
				tr.insert(arr[i]);
			else{
				ans = min(ans, tr.search_same_bits(arr[i]));
				tr.insert(arr[i]);
			}
		}
		return ans;
    }
};


int main()
{
	Solution s;
	int arr[3]={9, 5, 3};
	cout << s.minxorpair(3, arr) << endl;
}
