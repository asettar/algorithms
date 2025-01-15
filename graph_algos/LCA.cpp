#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

// LCA in log
// prblink: https://cses.fi/problemset/task/1688
// first make (u, v) on the same level
// try the max jump of size 2^i you can make so that nu != nv
// ans = will be par[nu] = par[nv]


const int MAXN = 2e5 + 10;
vector<vector <int>> adj;
int par[MAXN][21];
int lvl[MAXN];

void    binaryLifting(int node, int parent) {
    par[node][0] = parent;
    for (int i = 1; i < 21; i++) {
        if (par[node][i-1] != -1)
            par[node][i] = par[par[node][i-1]][i-1];
        else par[node][i] = -1;
    }

    if (parent == -1) lvl[node] = 0;
    else lvl[node] = 1 + lvl[parent];
    for (int child : adj[node]) {
        if (child == parent) continue;
        binaryLifting(child, node);
    }
}

int liftNode(int node, int k) {
    int cur = node;
    for (int i = 20; i >= 0; i--) {
        if (k & (1 << i))
            cur = par[cur][i];
        if (cur == -1) return -1;
    }
    return cur;
}

int LCA(int u, int v) {
    if (lvl[u] < lvl[v]) swap(u, v);
    u = liftNode(u, lvl[u] - lvl[v]); // u and v on same level
    if (u == v) return u; 
    for (int i = 20; i >= 0; i--) {
        if (par[u][i] != par[v][i]) 
            u = par[u][i], v = par[v][i];
    }
    return par[u][0];
}

int main() {
    memset(par, 0, sizeof(par));
    memset(lvl, 0, sizeof(lvl));

    int n, q; cin >> n >> q;
    adj = vector <vector<int>> (n + 1);
    for (int i = 2; i <= n; i++) {
        int num; cin >> num;
        adj[num].push_back(i);
        adj[i].push_back(num);
    }
    binaryLifting(1, -1);
    while (q--) {
        int u, v; cin >> u >> v;
        cout << LCA(u, v) << endl;
    }
}
