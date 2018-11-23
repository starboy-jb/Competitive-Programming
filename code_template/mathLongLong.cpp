#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef pair<ll , ll> PLL;
typedef long double ld;

#define pb push_back
#define all(c) c.begin(),c.end()
#define allr(c) c.rbegin(),c.rend()
#define mod 1000000007
#define PI 3.14159265
#define endl '\n'
#define MAX 100001

inline int add(ll x, ll y){ x += y; if(x >= mod) x -= mod; return x;}
inline int sub(ll x, ll y){ x -= y; if(x < 0) x += mod; return x;}
inline int mul(ll x, ll y){ return (x * 1ll * y) % mod;}
inline int powr(int a, ll b){
	int x = 1 % mod;
	while(b){
		if(b & 1) x = mul(x, a);
		a = mul(a, a);
		b >>= 1;
	}
	return x;
}
inline int inv(int a){ return powr(a, mod - 2);}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
