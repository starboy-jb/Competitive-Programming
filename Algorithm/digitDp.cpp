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
#define MAX 20

inline int add(int a, int b) {a += b; if (a < 0) a += mod; return a;}
inline int sub(int a, int b) {a -= b; if (a < 0) a += mod; return a;}
inline int mul(int a, int b) {return (a * 1ll * b) % mod;}
inline int pwr(int x, ll y) {
    int ans = 1 % mod;
    while (y) {
        if (y & 1) ans = mul(ans, x);
        x = mul(x, x);
        y >>= 1;
    }
    return ans;
}
inline int inv(int a) {return pwr(a, mod - 2);}

// How many numbers x are there in the range a to b, where the digit d occurs exactly k times in x?

vector <int> num;
int dp[MAX][MAX][2];
int k, x;

ll countNumber(int pos, int cnt, int flag) {
    if (cnt > k) return 0;
    if (pos == (int)num.size()) return cnt == k;
    if (dp[pos][cnt][flag] != -1) return dp[pos][cnt][flag];
    ll ans = 0;
    int can = (flag == 0? num[pos]: 9);
    for (int i = 0; i <= can; i++) {
        int nf = flag, ncnt = cnt;
        if (flag == 0 && i < num[pos]) nf = 1;
        if (i == x) ncnt++;
        if (ncnt <= k) ans += countNumber(pos + 1, ncnt, nf);
    }
    return dp[pos][cnt][flag] = ans;
}

ll solve(int b) {
    num.clear();
    while (b) {
        num.pb(b % 10);
        b /= 10;
    }
    reverse(all(num));
    memset(dp, -1, sizeof(dp));
    ll ans = countNumber(0, 0, 0);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll l, r;
    cin >> l >> r;
    cin >> x >> k;

    ll ans = solve(r) - solve(l - 1);

    debug(ans);

    return 0;
}
