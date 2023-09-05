#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

// prblinK: https://arena.moi/problem/mnpc22mnpc2022xmlsch

// attributes =  leaf
// accessing an object is equivalent to accessing all it's children
// cov(x) = numer of leafs under x that are accessible / number of totleafs under x


class trie{
	map<string, trie*> childs;
	bool is_leaf = 0;
	bool is_accessed = 0;
public:
	void	insert(vector<string> &v){
		trie *node = this;
		for(string &s : v){
			if (!node->childs.count(s)){
				trie *newn = new trie();
				node->childs[s] = newn;
			}
			node = node->childs[s];
		}
		node->is_leaf = 1;
		node->is_accessed = 0;
	}
	void	access_childs(){
		trie *node = this;
		node->is_accessed = 1;
		for(auto &p : node->childs){
			p.second->access_childs();
		}
	}
	void	access(vector<string> &v){
		trie *node = this;
		for(string s : v){
			node = node->childs[s];
		}
		node->access_childs();
	}

	void count_leafs_acc(double &lf, double &ac){
		trie *node = this;
		if(node->is_leaf)
			lf++;
		if(node->is_accessed)
			ac++;
		for(auto &p : node->childs)
			p.second->count_leafs_acc(lf, ac);
	}
	double	count(vector<string> &v){
		trie *node = this;
		for(string s : v)
			node = node->childs[s];
		double lf=0, ac=0;
		for(auto &p : node->childs){
			p.second->count_leafs_acc(lf, ac);
		}
		return (ac / lf);
	}
};

vector<string> getv(string s){
	vector<string> v;
	string sub;
	for(int i=1; i<=s.size(); i++){
		if (i == s.size() || s[i] == '/'){
			v.push_back(sub);
			sub.clear();
		}
		else
			sub += s[i];
	}
	return v;
}

int main()
{
	int n, q;
	cin >> n >> q;
	trie tr;
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		vector<string> v = getv(s);
		tr.insert(v);
	}
	while(q--){
		int type;
		string s;
		cin >> type >> s;
		vector<string> v = getv(s);
		if (type == 1){
			tr.access(v);
		}
		else
		{
			cout << fixed << setprecision(11);
			cout << tr.count(v) << endl;
		}
	}
}
