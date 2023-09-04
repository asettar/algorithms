#include <iostream>
#include<vector>
#include<map>
using namespace std;

// void get_all_strings (vector<string> &res)
// ● The function returns all the
// current strings in the trie sorted

class trie{
	map<char, trie*> childs;
	bool is_leaf = 0;
	vector<string> vals;
public:
	trie(){

	}
	void	insert(string s){
		trie *node = this;
		for(char c : s){
			if (!node->childs.count(c)){
				trie *newnode = new trie();
				node->childs[c] = newnode;
			}
			node = node->childs[c];
		}
		node->is_leaf = 1;
		node->vals.push_back(s);
	}
	void	get_all_paths(vector<string> &path){
		trie *node = this;
		if (node->is_leaf){
			path.insert(path.end(), node->vals.begin(), node->vals.end());
		}
		for(auto &p : node->childs){
			node = p.second;
			node->get_all_paths(path);
		}
	}
};

int	main()
{
    trie tr;
	tr.insert("abcd");
	tr.insert("xyz");
	tr.insert("a");
	tr.insert("ab");
	tr.insert("xyzw");
	tr.insert("bcd");
	tr.insert("bcd");
	vector<string> res;
	tr.get_all_paths(res);
	// sort(res.begin(), res.end());
	for(string s: res){
			cout << s << ' ';
	}
}
