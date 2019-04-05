/*input
abacaba

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
#define MAX 2001

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

vector <int> z_function(string str) {
    int n = str.size();
    int l = 0, r = 0;
    vector <int> z(n, 0);
    for (int i = 1; i < n; i++) {
        if (i <= r)
            z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && str[z[i]] == str[i + z[i]])
            ++z[i];
        if (i + z[i] > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    cin >> str;
    vector <int> vec = z_function(str);
    for (auto it : vec) {
        cout << it << " ";
    }
    cout << endl;

    return 0;
}
