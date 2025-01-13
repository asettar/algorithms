#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

// prblink: https://cses.fi/problemset/task/1687

// given a tree rooted at 1
// queries : x k -> find kth parent of node x
// target : knowing which node is k level above you

// the key is writing k in binary ex : k = 5 = 101 = 2^2 + 2^0
    // so I can go just to the parent that is 2^2 above , then 2^0 above
    // time Complexity : O(log)
// par[i][x] = parent of node i that is (1<<x) level above 
// par[i][x] = par[par[i][x-1]][x-1]
// because 2^x = 2^(x-1) + 2^(x-1)


// --------code
const int MAXN = 2e5 + 10;
vector<vector<int>> adj;
int par[MAXN][21];


void    binaryLifting(int node, int parent) {
    par[node][0] = parent;
    for (int i = 1; i < 21; i++) {
        if (par[node][i-1] != -1)
            par[node][i] = par[par[node][i-1]][i-1];
        else par[node][i] = -1;
    }

    for (int child : adj[node]) {
        if (child == parent) continue;
        binaryLifting(child, node);
    }
}

int query(int node, int k) {
    int cur = node;
    for (int i = 20; i >= 0; i--) {
        if (k & (1 << i))
            cur = par[cur][i];
        if (cur == -1) return -1;
    }
    return cur;
}

int main() {
    memset(par, 0, sizeof(par));

    int n, q; cin >> n >> q;
    adj = vector <vector<int>> (n + 1);
    for (int i = 2; i <= n; i++) {
        int num; cin >> num;
        adj[num].push_back(i);
        adj[i].push_back(num);
    }
    binaryLifting(1, -1);
    while (q--) {
        int x, k; cin >> x >> k;
        cout << query(x, k) << endl;
    }
}
