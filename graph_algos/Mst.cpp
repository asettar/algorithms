#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <climits>
#include <iomanip>
#include <numeric>
using namespace std;
#define int long long
#define double long double
#define vi vector <int>
#define vb vector <bool>
#define vs vector <string>
#define vvi vector <vi>
#define vvb vector <vb>
#define vvs vector <vs>
#define all(x) x.begin(), x.end()
#define	rall(x) x.rbegin(), x.rend()
#define endl '\n'
const int mod = 1e9+7;
const int maxn = 1e5 + 10;
 

// A spanning Tree : is a Tree where we have n nodes and n - 1 edges and all nodes are reachable
// from each other with minimum weight possible



void	solve()
{
	int n, m;
	while(cin >> n >> m){
		if (!n && !m) return;
		vector<vector<int>> edges(m);
		DisjointSet ds(n);
		for(int i = 0; i < m; i++){
			int u, v, w; cin >> u >> v >> w;
			edges[i] = {w, u, v};
		}
		int sumMstWeights = 0;
		sort(all(edges));
		vector<pair<int, int>> mstEdges;
		for(auto &e : edges) {
			int w = e[0], u = e[1], v = e[2];
			if (ds.findUPar(u) == ds.findUPar(v)) continue;
			sumMstWeights += w;
			ds.unionBySize(u, v);
			mstEdges.push_back({u, v});
		}
		if (ds.cnt == 1){
			cout << sumMstWeights << endl;
			for(auto [l, r] : mstEdges)
				cout << l << ' ' << r << endl;
		}
		else {
			cout << "No possible to have an Mst\n";
		}
    }
}
