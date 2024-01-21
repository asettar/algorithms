#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

// problem : there are 2*N chess players and N boards in a chess tournament.The rating of the chess player 
// is given by the array A. Every player can play only with one player.

// there is N board bairing to be done, and if you math player i and player j in the board K
// then the happiness Score increases by k * abs(a[i]-a[j]) * gcd(a[i], a[j]).
// Find the maxmimum happiness score you can make by designing a ideal pairing.
// N <= 10

int n;
vector<int> a;
vector<vector<int>> dp;

int rec(int i, int mask) {
	if (i == n) return 0;
	if (dp[i][mask] != -1) return dp[i][mask];
	int ans = 0;
	for(int i = 0; i < 2 * n; i++){
		for(int j = 0; j < 2 * n; j++){
			if ((mask & (1 << j)) || (mask & (1 << i))) continue;
			ans = max(ans, (i + 1) * abs(a[i] - a[j]) * gcd(a[i], a[j]) + rec(i + 1, mask | (1 << j) | (1 << i)));
		}
	}
	return dp[i][mask] = ans;
}

