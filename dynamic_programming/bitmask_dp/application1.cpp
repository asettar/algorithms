#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// in argument we keep a bitmask of elements taken/free --> max = O(2 ^ n) states
// new form  : dp(mask)  dp(i, mask), dp(mask1, mask2), dp(mask, k)

// problem : you have m students and n ranks each student i assigned to a rank j get a happyvalue = happy[i][j]
		// you need to find the best match for students to ranks that give the maximum value
		// n = 15, m = 50
	
int n, m;
vector<vector<int>> happy;
vector<vector<int>> memo;

// time com = O(M * N * 2 ^ N)

int rec(int i, int mask){
	if (i == m) return 0;
	if (memo[i][mask] != -1) return memo[i][mask];

	int ans = 0;
	for(int j = 0; j < n; j++){
		if ((mask & (1 << j)) == 0)
			ans = max(ans, happy[i][j] + rec(i + 1, mask | (1 << j)));
	}
	return (memo[i][mask] = ans);
}

int32_t	main() {
	cin >> n >> m;
	cout << rec(0, 0) << endl;   // will give the ans
}
