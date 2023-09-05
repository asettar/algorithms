#include <iostream>
#include <vector>
using namespace std;

// prblink:https://leetcode.com/problems/implement-magic-dictionary/


class MagicDictionary {
	MagicDictionary *childs[26];
	bool is_leaf;
public:
    MagicDictionary() {
        memset(childs, 0, sizeof(childs));
		is_leaf = 0;
    }
    
    void buildDict(vector<string> dictionary) {
        for(string s : dictionary){
			MagicDictionary *node = this;
			for(char c : s){
				if (node->childs[c-'a'] == nullptr){
					MagicDictionary *newnode = new MagicDictionary();
					node->childs[c-'a'] = newnode;
				}
				node = node->childs[c-'a'];
			}
			node->is_leaf = 1;
		}
    }
    // hello ciborg     cello
	bool possible(MagicDictionary *node, int i, string searchWord){
		for(int j=i; j<searchWord.size(); j++){
			if (node->childs[searchWord[j]- 'a'] == nullptr)
				return false;
			node = node->childs[searchWord[j] - 'a'];
		}
		return node->is_leaf;
	}
    bool search(string searchWord) {
        MagicDictionary *node = this;
		for(int i=0; i<searchWord.size(); i++){
			for(char cc = 'a'; cc <= 'z'; cc++){
				if (cc == searchWord[i])
					continue;
				if (node->childs[cc- 'a'] != nullptr){
					if (possible(node->childs[cc- 'a'], i+1, searchWord))
						return true;
				}
			}
			if (node->childs[searchWord[i]- 'a'] == nullptr)
				return false;
			node = node->childs[searchWord[i]- 'a'];
		}
		return false;
    }
};



int main()
{
	MagicDictionary mg;
	mg.buildDict({"hello", "leetcode"});
	cout << mg.search("hellg") << endl;
	cout << mg.search("hhllo") << endl;
	cout << mg.search("hell") << endl;
	cout << mg.search("leetcoded") << endl;
}
