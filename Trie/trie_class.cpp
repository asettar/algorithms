#include <iostream>
using namespace std;


struct Node{
	Node *links[26];
	bool flag=false;

	// check if the reference trie is present
	bool contain_key(char ch){   // if it is null the there is no char ch
		return (links[ch-'a'] != nullptr);
	}

	//creating refernce trie
	void	put(char ch, Node *node){
		links[ch-'a'] = node;
	}

	// to get to the next node for traversal
	Node	*get(char ch){
		return links[ch - 'a'];
	}

	// set the flag to true at the end of the word
	void	set_end(){
		flag = true;
	}
	
	// check if the word is completed or not 
	bool	is_end(){
		return flag;
	}
};

class trie{
private :
	Node *root;
public:
	//initialize the structure 
	trie(){
		root = new Node();
	}

	// insert a word into the trie
	void	insert(string word){
		Node *node = root;   // start from the root
		for(int i=0; i<word.size(); i++){
			if (!node->contain_key(word[i]))
				node->put(word[i], new Node());
			node = node->get(word[i]);
		}
		node->set_end();
	}

	// check if a word exist in the trie
	bool search(string word){
		Node *node = root;
		for(int i=0; i<word.size(); i++){
			if (!node->contain_key(word[i]))
				return false;
			node = node->get(word[i]);
		}
		return node->is_end();
	}

	// check if there is a word in the trie that start with prefix

	bool start_with(string prefix){
		Node *node = root;
		for(int i=0; i<prefix.size(); i++){
			if (!node->contain_key(prefix[i]))
				return false;
			node = node->get(prefix[i]);
		}
		return true;
	}
};


int	main()
{
  
}
