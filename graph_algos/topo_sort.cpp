#include <bits/stdc++.h>
using namespace std;


// topo sort when you have something depend on something
// the graph must be acyclic and directed (it can be disconnected too np)
// if the ans array wich contains the oredering doennt contain N nodes then the graph have cycles cant be ordered
// time complexity O(E+V)
vector<int> topo_sort(vector<vector<int>> &adj)
{
	int n = adj.size();
	vector<int> ans;
	vector<int> indegree(n);    // compute the indegree of a node
	for(int i=0; i<n; i++)
	{
		for(int j:adj[i])
			indegree[j]++;
	}
	queue<int> q;   // we put the node that have indegree 0 (doesnt depend on anything)
	for(int i=0; i<n; i++)
	{
		if (!indegree[i])
			q.push(i);
	}
	while(!q.empty())
	{
		int curr = q.front();
		q.pop();
		ans.push_back(curr);
		for(int j : adj[curr])
		{
			indegree[j]--;
			if (!indegree[j])
				q.push(j);
		}
	}
	return ans;
}
