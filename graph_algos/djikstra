#include <bits/stdc++.h>
using namespace std;

struct edge
{
	int to, w;
	bool	operator<(const edge &e)const{
		return w>e.w;
	}
};

void	djikstra(vector<vector<edge>> &adjlist, int n, int src)
{
	vector<int> dist(n, 1e9);
	vector<bool> vis(n);
	dist[src]=0;
	priority_queue<edge> pq;
	pq.push({src, 0});
	while (!pq.empty())
	{
		// get node with minimum disitance
		edge mnEdge = pq.top();
		pq.pop();
		int mnIdx = mnEdge.to;
		for(edge &e : adjlist[mnIdx])
		{
			if(!vis[e.to] && dist[e.to] > mnEdge.w + e.w)
			{
				dist[e.to] = mnEdge.w + e.w;
				pq.push({e.to, dist[e.to]});
			}
		}
		vis[mnEdge.to]=1;
	}
}
