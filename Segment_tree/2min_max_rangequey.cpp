#include <iostream>
#include <vector>
#include<climits>

using namespace std;

// get the min or max for range from l to r in only O(log) instead of linear time O(r-l+1)
// segment tree is like a binary tree that is stored in an array with size 4*n the first node(which have index 0) have the min element in the array from 0 to n-1
// then you split each node to 2   (left node have the minimum from(l, mid) && right node have minumum from (mid+1, r)
// build : O(N)
// ind variable dont have any relation with index of the array (that you re searching min in it) it just represent the index of the child

void	build(int ind, int low, int high, vector<int> arr, vector<int> &seg)
{
	if (low == high)
	{
		seg[ind] = arr[low];
		return ;
	}
	int mid=(low+high)/2;
	build(2*ind +1, low, mid, arr, seg);
	build(2*ind +2, mid + 1, high, arr, seg);
	seg[ind] = min(seg[2*ind + 1], seg[2*ind +2]);
}

// query : to compute the min in range (l, r) : there is 3 case we can define:
// partial overlap of node with range L, R 	, go to left, go to right return min(left,right) (for example if  l, r = 2, 4  &&  low, high = 0, n-1)
// no overlap with range (L, R) return INT_MAX. node index out of range we dont need it in our calculations
// complete overlap with (L, R); when a node index rely entirely in the given range(l to r)--> return seg[index] 
// query : O(log(N))
int	query(int ind, int low, int high, int l, int r, vector<int> &seg)
{
	if (high < l || r < low)
		return INT_MAX; 
	if (l >= low && r <= high)
		return seg[ind];
	int mid = (low + high) / 2;
	int left = query(2 * ind + 1, low, mid, l, r, seg);
	int right = query(2 * ind + 2, mid + 1, high, l ,r, seg);
	return min(left, right);
}

// Point update : let's say you are given an index and a new value for that index, so you need to update the segment tree
 // time comp: O(N) in avg
void	update(int ind, int low, int high, int i, int val, vector <int> &seg)
{
	if (low == high)
	{
		seg[ind] = val;
		return ;
	}
	int mid = (low + high) / 2;
	if (i <= mid)
		update(2*ind+1, low, mid, i, val, seg);
	else
		update(2 * ind +2, mid+1, high, i, val, seg);
	seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
}

int	main()
{
	int n;	cin >> n;
	vector<int> arr(n);
	for (int i=0; i < n; i++)
		cin >> arr[i];
	vector <int> seg(4*n);
	build(0, 0, n-1, arr, seg);  // build the seg tree index 0 have the min of all array
	cout << seg[0] << endl;
	int q;
	cin >> q;
	while (q--)
	{
		int l, r;
		cin >> l >> r;    // give the min of the array between l and r (0 base indexing)
		cout << query(0, 0, n-1, l, r, seg) << endl; // qlays start ind with 1 
	}
}
