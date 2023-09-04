#include <bits/stdc++.h>
using namespace std;

struct BinaryTree
{
	BinaryTree *left{};
	BinaryTree *right{};
	int data{};
	BinaryTree(int data){
		data = data;
	}
	void	print_postorder()
	{
		if(left)
			left->print_postorder();
		if(right)
			right->print_postorder();
		cout << data << ' ';
	}
	// new constructor takes string postfix ex : 23+4* and build the tree
	// when you call post_order(LRV) it must output same string
	BinaryTree(string postfix) 
	{
		stack<BinaryTree *> tree;
		for(int i=0; i < postfix.size(); i++)
		{
			BinaryTree *cur = new BinaryTree(postfix[i]);
			if(!isdigit(postfix[i])){
				cur->right = tree.top();
				tree.pop();
				cur->left = tree.top();
				tree.pop();
			}
			tree.push(cur);
		}
		BinaryTree *root = tree.top();
		this->data = root->data;
		this->left = root->left;
		this->right = root->right;
	}
<<<<<<< HEAD
	void	level_order_traversal()
	{
		queue<BinaryTree *> q;
		q.push(this);
		for(int level = 0, sz=q.size(); !q.empty(); level++, sz=q.size())
		{
			cout << "Level " << level << ": ";
			while(sz--)
			{
				BinaryTree *cur = q.front();
				q.pop();
				cout << cur->data << ' ';
				if(cur->left)
					q.push(cur->left);
				if(cur->right)
					q.push(cur->right);
			}
			cout << "\n";
		}
	}
=======
>>>>>>> c42cb41542b5355e13beb5e72bc81fe9d7a479ac
	void	traverse_left_boundary() // print the nodes that are on the left boundary
	{
		queue<BinaryTree *> q;
		q.push(this);
		while(!q.empty()){
			BinaryTree *cur = q.front();
			q.pop();
			cout << cur->data << " ";
			if(cur->left)
				q.push(cur->left);
			else if (cur->right)  // if there are no left nodes, the right node if exists is in the boundary
				q.push(cur->right);
		}
		cout << "\n";
	}
	void	traverse_left_boundary_rec() // recursively
	{
		cout << data << " ";
		if (left)
			left->traverse_left_boundary_rec();
		else if (right)
			right->traverse_left_boundary_rec();
	}
	pair<int, int> binary_tree_diameter()  // the lenght of the longuest path between two nodes in a tree
	{
		// keep track of diam and height;
		pair<int, int> res ={0, 0};
		pair<int, int> right_diam = {0, 0};
		pair<int, int> left_diam= {0, 0};
		if(left){
			left_diam = left->binary_tree_diameter();
			res.first += 1 + left_diam.second;
		}
		if(right){
			right_diam = right->binary_tree_diameter();
			res.first += 1 + right_diam.second;
		}
		res.first = max({res.first, right_diam.first, left_diam.first});
		// normal height computation
		res.second = max({res.second, 1 + left_diam.second, 1 + right_diam.second});
		return res;
	}
};
