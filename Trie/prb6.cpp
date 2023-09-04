#include <iostream>
#include <map>
#include <vector>
using namespace std;


//  Problem #6: OS Paths
// ● Assume for simplicity a system path represented as vector of strings 
// 	○ /home/software/eclipse/bin ⇒ {"home", "software", "eclipse", "bin"}
// ● Design a trie
// ○ void insert(const vector<string> &path) ⇒ adds a path to the trie
// ○ bool subpath_exist(const vector<string> &path) ⇒ True if such sub-path ex
 

class trie{
	map<string, trie*> childs;
	bool is_leaf;
public:
	trie(){
	}
	void	insert(const vector<string> &path){
		trie *node = this;
		for(string s : path){
			if (!node->childs.count(s)){
				trie *newnode = new trie();
				node->childs[s] = newnode;
			}
			node = node->childs[s];
		}
		node->is_leaf = true;
	}
	bool	subpath_exist(const vector<string> &path){
		trie *node = this;
		for(string s : path){
			if (!node->childs.count(s))
				return false;
			node = node->childs[s];
		}
		return true;
	}
};

int main()
{
  
}
