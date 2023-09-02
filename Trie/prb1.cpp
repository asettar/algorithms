#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


//prb link :  https://bit.ly/3n3kedU

struct Node {
  Node * links[26];
  int cntEndWith = 0;
  int cntPrefix = 0;

  bool containsKey(char ch) {
    return (links[ch - 'a'] != NULL);
  }
  Node * get(char ch) {
    return links[ch - 'a'];
  }
  void put(char ch, Node * node) {
    links[ch - 'a'] = node;
  }
  void increaseEnd() {
    cntEndWith++;
  }
  void increasePrefix() {
    cntPrefix++;
  }
  void deleteEnd() {
    cntEndWith--;
  }
  void reducePrefix() {
    cntPrefix--;
  }
  int getEnd() {
    return cntEndWith;
  }
  int getPrefix() {
    return cntPrefix;
  }
};
class Trie {
  private:
    Node * root;

  public:
    /** Initialize your data structure here. */
    Trie() {
      root = new Node();
    }

  /** Inserts a word into the trie. */
  void insert(string word) {
    Node * node = root;
    for (int i = 0; i < word.length(); i++) {
      if (!node -> containsKey(word[i])) {
        node -> put(word[i], new Node());
      }
      node = node -> get(word[i]);
      node -> increasePrefix();
    }
    node -> increaseEnd();
  }
 bool isComplete(string word){
	Node *node = root;
	for(int i=0; i<word.size(); i++){
		node = node->get(word[i]);
		if (node->cntEndWith == 0)
			return 0;
	}
	return 1;
 }

 int countWordsEqualTo(string &word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (node->containsKey(word[i]))
            {
                node = node->get(word[i]);
            }
            else
            {
                return 0;
            }
        }
        return node->getEnd();
    }


  int countWordsStartingWith(string & word) {
    Node * node = root;
    for (int i = 0; i < word.length(); i++) {
      if (node -> containsKey(word[i])) {
        node = node -> get(word[i]);
      } else {
        return 0;
      }
    }
    return node -> getPrefix();
  }

  void erase(string & word) {
    Node * node = root;
    for (int i = 0; i < word.length(); i++) {
      if (node -> containsKey(word[i])) {
        node = node -> get(word[i]);
        node -> reducePrefix();
      } else {
        return;
      }
    }
    node -> deleteEnd();
  }
};

bool compare(string &a, string &b){
	if (a.size() != b.size())
		return (a.size() > b.size());
	return a < b;

}

string	completeString(int n, vector<string> &a){
	vector<string> ans;
	Trie t;
	for(int i=0; i<n; i++){
		t.insert(a[i]);
	}
	for(int i=0; i<n; i++){
		if (t.isComplete(a[i]))
			ans.push_back(a[i]);
	}
	sort(ans.begin(), ans.end(), compare);
	if (!ans.empty())
		return ans[0];
	return "None";
}
