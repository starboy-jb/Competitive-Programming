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
#define debug(x) cout << #x << " = " << x << endl;
#define MAX 


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b;
    cin >> a >> b;
    int t1, s1, t0, s0, r0 = a, r1 = b;
    s0 = t1 = 1;
    t0 = s1 = 0;
    while (1) {
        if (!r1) break;
        int q = r0 / r1;
        int r = r0 % r1;
        int sc = s0 - s1 * q;
        int tc = t0 - t1 * q;
        r0 = r1;
        r1 = r;
        t0 = t1;
        s0 = s1;
        s1 = sc;
        t1 = tc;
    }
    cout << s0 << " " << t0 << endl;

    return 0;
}
