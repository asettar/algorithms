#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
using namespace std;


// prblink : https://leetcode.com/problems/design-add-and-search-words-data-structure/
// beats 80 %
class WordDictionary {
	vector<WordDictionary*> links;
	int end;
public:
    WordDictionary() {
		links = vector<WordDictionary*> (26);
		end = 0;
    }
    
    void addWord(string word) {
		WordDictionary *node = this;
        for(char c : word){
			if (node->links[c - 'a'] == nullptr)
				node->links[c - 'a'] = new WordDictionary();
			node = node->links[c - 'a'];
		}
		node->end = 1;
    }
    
	bool search(int index, string &word){
		if (index == word.size()) return this->end;
		bool ans = 0;
		if (word[index] == '.'){
			for(int i = 0; i < 26; i++){
				if (this->links[i] != nullptr)
					ans = ans || this->links[i]->search(index + 1, word);
			}
		}

		else {
			if (this->links[word[index] - 'a'] == nullptr) ans = 0;
			else ans = this->links[word[index] - 'a']->search(index + 1, word);
		}
		return ans;
	}

    bool search(string word) {
        return search(0, word);
    }
};


int main(){
	WordDictionary *w = new WordDictionary();
	w->addWord("bad");
	w->addWord("dad");
	w->addWord("mad");
	cout << w->search("pad") << endl;// return False
	cout << w->search("bad") << endl; // return True
	cout << w->search(".ad") << endl; // return True
	cout << w->search("b..") << endl;

}
