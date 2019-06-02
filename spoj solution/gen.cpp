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
#define MAX 1501

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

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    srand(atoi(argv[1]));
    int mx = 100;
    int test = 2;
    cout << test << endl;
    while (test--) {
      int r = rand(1, 6);
      int c = rand(1, 6);
      cout << r << " " << c << endl;
      for (int i = 0; i < r; i++) {
        cout << rand(1, c) << " ";
      }
      cout << endl;
      for (int i = 0; i < c; i++) {
        cout << rand(1, r) << " ";
      }
      cout << endl;
    }
    
    
    return 0;
}
