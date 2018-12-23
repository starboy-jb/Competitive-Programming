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
#define MAX 

bool isPrime (ll n) {
    if(n == 1) return 0;
    if(n == 2 or n == 3) return 1;
    if(n % 2 == 0 or n % 3 == 0) return 0;

    for(ll i = 5; i * i <= n; i += 6) if(n % i == 0 or n % (i + 2) == 0) return 0;
    return 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
