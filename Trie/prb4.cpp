#include <iostream>
#include <vector>
using namespace std;

// prblink:https://leetcode.com/problems/replace-words/

struct Node{
	Node *links[26];
	bool is_leaf=0;

	bool contain(char c){
		return (links[c-'a'] != nullptr);
	}
	void put(Node *node, char c){
		links[c - 'a'] = node;
	}
	Node *getnext(char c){
		return links[c-'a'];
	}
	void setend(){
		is_leaf = 1;
	}
};

class trie{
	Node *root;
public:
	trie(){
		root = new Node();
	}
	void insert(string s){
		Node *node = root;
		for(char c : s){
			if (!node->contain(c)){
				node->put(new Node(), c);
			}
			node = node->getnext(c);
		}
		node->setend();
	}
	string search_root(string s){
		Node *node = root;
		string ans;
		for(int i=0; i<s.size(); i++){
			if (node->contain(s[i]))
			{
				ans += s[i];
				node = node->getnext(s[i]);
			}
			else{
				ans += s.substr(i);
				return ans;
			}
			if (node->is_leaf)
				return ans;
		}
		return ans;
	}
};

class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
		trie tr;
		for(string s : dict)
			tr.insert(s);
		string ans, sub;
		for(int i=0; i<=sentence.size(); i++){
			if (i == sentence.size() || sentence[i] == ' '){
				// cout << sub << "::"<<endl;
				ans += tr.search_root(sub);
				if (i != sentence.size())
					ans += ' ';
				sub.clear();
			}
			else
				sub += sentence[i];
		}
		return ans;
    }
};

int	main()
{
	vector<string> dict={"cat","bat","rat"};
	Solution s;
	cout << s.replaceWords(dict, "the cattle was rattled by the battery") << endl;

	dict={"a","b","c"};
	cout << s.replaceWords(dict, "aadsfasf absbs bbab cadsfafs") << endl;
}
