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
	void	print_inorder(){
		if(left)
			left->print_inorder();
		cout << data <<" ";
		if(right)
			right->print_inorder();
	}
	void	print_inorder_iterative() // iterative inorder traversal(replace recursion with a stack)
	{
		stack <pair<BinaryTree *, bool>> s;
		s.push({this, false});
		while(!s.empty())
		{
			BinaryTree *cur = s.top().first;
			bool is_done = s.top().second;
			s.pop();
			// if expanded already and we are here, then we just returned from recursion
			if(is_done)
				cout << cur->data << " ";
			else{
				if(cur->right)
					s.push({cur->right, false});
				s.push({cur, true});
				if(cur->left)
					s.push({cur->left, false});
			}
		}
		cout << "\n";
	}
	int	tree_max()  // get the maximum of btree nodes values
	{
		int mx = data;
		if(left)
			mx = max(mx, left->tree_max());
		if(right)
			mx = max(mx, right->tree_max());
		return mx;
	}
	int	tree_height()    // get the btree height
	{
		int ans = 0;
		if (left)
			ans = max(ans, 1 + left->tree_height());
		if(right)
			ans = max(ans, 1 + right->tree_height());
		return ans;
	}
	int	total_nodes()       // get the total nodes of the btree
	{
		int ans = 1;
		if(left)
			ans += left->total_nodes();
		if(right)
			ans += right->total_nodes();
		return ans;
	}
	bool is_exists(int value)   // check if a value exists
	{
		bool ans = 0;
		if (data == value)
			return 1;
		if(left)
			ans = left->is_exists(value);
		if(!ans && right)
			ans = right->is_exists(value);
		return ans;
	}
	bool is_perfect(int h = -1)     // check if the btree represents a perfect btree
	{
		if (h == -1)
			h = tree_height(); // first call
		if(!left && !right)
			return h == 0; // must be the last level if this condition is true
		if((left && !right) || (right && !left))
			return false;
		return left->is_perfect(h-1) && right->is_perfect(h-1);
	} 
	bool is_perfect_formula()
	{
		return (total_nodes() == pow(2, tree_height() + 1) - 1);
	}
	void clear()    // clear the memory allocated by childrens
	{
		if(left){
			delete left;
			left = nullptr;
		}
		if(right){
			delete right;
			right = nullptr;
		}
	}
	~BinaryTree(){
		clear();
	}
	
};

int main()
{
  
}
