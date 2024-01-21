#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// problem(hamiltonian walk) : a City is modelled using a Graph with N nodes and M edges. The nodes are numbered from 1 to N
// there is a Person standing at node1, and wants to visit a freind at City N, He wants to visit 
// evert City exactly once. Find the number or paths that exists of this form  N <= 20

// person need to visit all city from 1 2 3 .. N exactly once

int n;
vector<vector<int>> neigh;
vector<vector<int>> memo;

int rec(int i, int mask){
	if (i == n) return (mask = ((1 << n) - 1));
	if (memo[i][mask] != -1) return memo[i][mask];
	int ans = 0;
	for(int v : neigh[i]){
		if (mask & (1 << (v - 1))) continue;
		ans += rec(i + 1, mask | (1 << (v - 1)));
	}
	return memo[i][mask] = ans;
}

int	main() {
	cin >> n;
	cout << rec(0, 0) << endl;
}
