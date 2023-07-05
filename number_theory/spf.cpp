#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define vi vector<int>
#define all(x) x.begin(), x.end()
#define	rall(x) x.rbegin(), x.rend()
#define endl '\n'
const int mod = 1e9+7;
const int maxn = 1e5 + 10;
 
//smallest prime factor
int	spf[MAXN];
void	spf_seive()
{
	memset(spf, 0, sizeof(spf));
	for(int i = 2; i < MAXN; i++){
		if (prime[i]){
			for(int j = i; j < MAXN; j += i){
				if (spf[j] == 0)
					spf[j] = i;
			}
		}
	}
}

