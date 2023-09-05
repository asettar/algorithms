#include <iostream>
using namespace std;

//prblink:https://www.codingninjas.com/studio/problems/count-distinct-substrings_985292?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_tries_videos

struct Node{
	Node *childs[26];
	bool is_leaf;
};

int countDistinctSubstrings(string &s)
{
	Node *root  = new Node();
	int cnt = 1, n = s.size();
	for(int i=0; i<n; i++){
		Node *node = root;
		for(int j=i; j<n; j++){
			if (node->childs[s[j]- 'a'] == nullptr){
				cnt++;
				Node *newnode = new Node();
				node->childs[s[j]- 'a'] = newnode;
			}
			node = node->childs[s[j]-'a'];
		}
		// cout << cnt << endl;
	}
	return cnt;
}

int main()
{
	string s = "sds";
	cout << countDistinctSubstrings(s) << endl;
	s = "aa";
	cout << countDistinctSubstrings(s) << endl;
}
