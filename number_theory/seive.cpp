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
 
bool prime[maxn];
void	prime_seive()
{
	for(int i=1; i< maxn; i++)
		prime[i] = true;
	prime[0] = prime[1] = false;
	for(int i=2; i<maxn; i++)
	{
		if (prime[i])
		{
			for (int j=i*i; j< maxn ;j+=i)
				prime[j] = false;
		}
	}
}
