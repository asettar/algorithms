#include <bits/stdc++.h>
using namespace std;


class DisjointSet
{ 
	vector<int> rank, parent, size;
public: 
	DisjointSet(int n)
	{
		rank.resize(n+1);       // n+1 if the graph is 1 based
		parent.resize(n+1);
		for(int i=0; i<=n; i++)
			parent[i] = i;
		size.resize(n+1, 1);
	}
	int	findUPar(int node)				//findultimateparent
	{
		if (node == parent[node])
			return node;
		return parent[node] = findUPar(parent[node]);   // path compression (max : log n)
	}
	void	unionByRank(int u, int v)
	{
		int ulp_u = findUPar(u);
		int ulp_v = findUPar(v);
		if (ulp_v == ulp_u)   // already connected(same ul_parent)
			return ;
		if (rank[ulp_v] < rank[ulp_u])
			parent[ulp_v] = ulp_u;
		else if (rank[ulp_u] < rank[ulp_v])
			parent[ulp_u] = ulp_v;
		else
		{
			parent[ulp_v] = ulp_u;
			rank[ulp_u]++;
		}
	}
	void	unionBySize(int u, int v)
	{
		int ulp_u = findUPar(u);
		int ulp_v = findUPar(v);
		if (ulp_u == ulp_v)
			return ;
		if (size[ulp_u] < size[ulp_v])
		{
			parent[ulp_u] = ulp_v;
			size[ulp_v]  += size[ulp_u];
		}
		else
		{
			parent[ulp_v] = ulp_u;
			size[ulp_u] += size[ulp_v];
		}
	}

};
