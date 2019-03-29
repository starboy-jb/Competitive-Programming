/*input

*/

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
int mod = 1000000007;
#define PI 3.14159265
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl;
#define MAX 10000001

template < typename T > T GCD(T a, T b)            { ll t; while(a) { t = a; a = b % a; b = t; } return b; }
template < typename T > string toString(T a)       { return to_string(a); }
template < typename T > void toInt(string s, T &x) { stringstream str(s); str >> x;}
inline int add(ll a, ll b) {a += b; if (a < 0) a += mod; return a;}
inline int sub(ll a, ll b) {a -= b; if (a < 0) a += mod; return a;}
inline int mul(ll a, ll b) {return (a * 1ll * b) % mod;}
inline int pwr(ll x, ll y) {
    int ans = 1 % mod;
    while (y) {
        if (y & 1) ans = mul(ans, x);
        x = mul(x, x);
        y >>= 1;
    }
    return ans;
}
inline int inv(int a) {return pwr(a, mod - 2);}

vector <int> seiveSundram(int n) {
    int newN = (n - 2) / 2;
    bool mark[newN + 1];
    memset(mark, false, sizeof(mark));
    vector <int> primes;
    if (n >= 2) primes.pb(2);

    for (int i = 1; i <= newN; i++) {
        for (int j = i; i + j + 2 * i * j <= newN; j++) {
            mark[i + j + 2 * i * j] = true;
        }
    }
    for (int i = 1; i <= newN; i++) {
        if (!mark[i]) {
            primes.pb(2 * i + 1);
        }
    }
    return primes;

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector <int> primes = seiveSundram(n);
    for (auto it : primes) {
        cout << it << " ";
    }
    cout << endl;

    return 0;
}
