/*input
2
3 2
2 1 0 
1 2 
3 3
3 2 1 
1 2 2

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
int mod = 998244353;
#define PI 3.14159265
#define endl '\n'
#define F first
#define S second
#define debug(x) cout << #x << " = " << x << endl;
#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cout << name << " : " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif


template < typename T > T GCD(T a, T b)            { ll t; while(a) { t = a; a = b % a; b = t; } return b; }
template < typename T > string toString(T a)       { return to_string(a); }
template < typename T > void toInt(string s, T &x) { stringstream str(s); str >> x;}
inline int add(int x, int y){ x += y; if(x >= mod) x -= mod; return x;}
inline int sub(int x, int y){ x -= y; if(x < 0) x += mod; return x;}
inline int mul(int x, int y){ return (x * 1ll * y) % mod;}
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

  int test;
  cin >> test;
  while (test--) {
    int r, c;
    cin >> r >> c;
    vector <ll> vec1, vec2; 
    ll v;
    ll s1 = 0, s2 = 0;
    for (int i = 0; i < r; i++) {
      cin >> v;
      vec1.pb(v);
      s1 += v;
    }
    for (int i = 0; i < c; i++) {
      cin >> v;
      vec2.pb(v);
      s2 += v;
    }
    bool ok = true;
    if (s1 != s2) {
      ok = false;
    }
    else {
      ll sum = 0;
      sort(allr(vec1));
      for (auto it : vec1) {
        v = it;
        sort(allr(vec2));
        for (auto &itr : vec2) {
          if (!v) break;
          if (itr) {
            sum++;
            itr--;
            v--;
          }
        }
      }
      ok = (sum == s2);
    }
    cout << (ok? "YES": "NO") << endl;
  }


  return 0;
}
