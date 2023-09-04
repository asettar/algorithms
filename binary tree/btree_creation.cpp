#include <bits/stdc++.h>
using namespace std;

void build(vector<node*> &a, string s)
{
	for(int i=0; i<a.size()-1; i++){
		if(s[i] == 'L')
			a[i]->left = a[i+1];
		else
			a[i]->right = a[i+1];
	}
}

node *btree_create(vector<vector<node>> &path, vector<string> &s)
{
	node *root;
	for(int i=0; i<path.size(); i++)
	{
		build(path[i], s[i]);
	}
}

int main()
{
	node *root;
	vector<node> path
}
