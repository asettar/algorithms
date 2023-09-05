#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

// prblink: https://leetcode.com/problems/prefix-and-suffix-search/

class ivtrie{
public:
map<char, ivtrie*> childs;
set<int, greater<int>> s;
	ivtrie(){
	}
	void	insert(string s, int idx){
		ivtrie *node = this;
		for(int i=s.size()-1; i>=0; i--){
			if (node->childs.count(s[i]) == 0){
				ivtrie *newn = new ivtrie();
				node->childs[s[i]] = newn;
			}
			node = node->childs[s[i]];
			node->s.insert(idx);
		}
	}
	ivtrie*  starts(string suf){
		ivtrie *node = this;
		for(int i=suf.size()-1; i>=0; i--){
			if (node->childs.count(suf[i]) == 0)
				return nullptr;
			node = node->childs[suf[i]];
		}
		return node;
	}
};

class trie{

public:
	map<char, trie*> childs;
	set<int, greater<int>> s;
	trie(){
	}
	void	insert(string s, int idx){
		trie *node = this;
		for(char c : s){
			if (node->childs.count(c) == 0){
				trie *newn = new trie();
				node->childs[c] = newn;
			}
			node = node->childs[c];
			node->s.insert(idx);
		}
	}
	trie*  starts(string pre){
		trie *node = this;
		for(char c : pre){
			if (node->childs.count(c) == 0)
				return nullptr;
			node = node->childs[c];
		}
		return node;
	}
};


class WordFilter {
public:
	trie tr;
	ivtrie trv;
    WordFilter(vector<string>& words) {
		for(int i=0; i<words.size(); i++){
			tr.insert(words[i], i);
			trv.insert(words[i], i);
		}
    }
    
    int f(string pref, string suff){
        trie *p = tr.starts(pref);
		if (p == nullptr)
			return -1;
		ivtrie *s = trv.starts(suff);
		if (s==nullptr)
			return -1;
		for(int i : p->s){
			if (s->s.count(i))
				return i;
		}
		return -1;
    }
};

int main()
{
	vector<string> v={"Wordfilter", "f"};
	WordFilter w(v);
	cout << w.f( "W", "er") << endl;

}
