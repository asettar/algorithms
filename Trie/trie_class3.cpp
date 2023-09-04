#include <iostream>
#include <map>
using namespace std;


// more memory efficent implementation based on map

class trie{
	map<char, trie*> childs;
	trie *root;
	bool is_leaf;
public:
	trie(){
	}
	void	insert(string s){
		trie *node = root;
		for(char c : s){
			if (!node->childs.count(c) == 0){
				trie *newnode = new trie();
				node->childs[c] = newnode;
			}
			node = node->childs[c];
		}
		node->is_leaf = true;
	}
	void	
};

int main()
{
  
}
