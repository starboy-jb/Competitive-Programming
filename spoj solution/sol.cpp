/*input
1
3
10 10 1

*/
 
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <bitset>
#include <numeric>
 
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
const int INF = 1034567891;
const ll LL_INF = 1234567890123456789ll;
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
 
#define out(container) for (auto it : container) cout << it << " "; cout << endl;
 
 
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
    int n;
    cin >> n;
    ll v;
    vector <ll> vec;
    for (int i = 0; i < n; i++) {
      cin >> v;
      vec.pb(v);
    }
    ll ans = LL_INF;
    queue <pair<ll, vector <ll> > > qu;
    map <pair <ll, vector <ll> >, pair <ll, vector <ll> > > par;
    vector <ll> kaun;
    qu.push({0, vec});
    while (!qu.empty()) {
      auto it = qu.front();
      vec = it.S;
      ll p = it.F;
      qu.pop();
      int ind = 0;
      ll cur = LL_INF;
      n = vec.size();
      if (vec.size() == 2) {
        p += vec[0] + vec[1];
        if (p < ans) {
          ans = p;
          kaun = vec;
          par[{ans, kaun}] = {p - vec[0] - vec[1], vec};
        }
        continue;
      }
      for (int i = 0; i < n; i++) {
        int nxt = (i + 1) % n;
        if (vec[i] + vec[nxt] < cur) {
          cur = vec[i] + vec[nxt];
          ind = i;
        }
      }
      vector <int> idx;
      for (int i = 0; i < n; i++) {
        int nxt = (i + 1) % n;
        if (vec[i] + vec[nxt] == cur) {
          idx.pb(i);
        }
      }
      
      ll tp = 0;
      // debug(idx.size());
      for (auto it : idx) {
        vector <ll> temp;
        if (it == n - 1) {
          for (int i = 1; i < n - 1; i++) {
            temp.pb(vec[i]);
          }
          temp.pb(vec[0] + vec[n - 1]);
          tp = p + vec[0] + vec[n - 1];
        } else {
          for (int i = 0; i < n; i++) {
            if (i == it) {
              tp = p + vec[i] + vec[i + 1];
              temp.pb(vec[i] + vec[i + 1]);
              i++;
            } else {
              temp.pb(vec[i]);
            }
          }
        }
        // out(temp);
        par[{tp, temp}] = {p, vec};
        qu.push({tp, temp});
      }
      // cout << endl;
    }
    ll tp = ans;
    vector <ll> temp = kaun;
    vector <pair<ll, vector <ll> > > farzi;
    while (tp != 0) {
      auto it = par[{tp, temp}];
      tp = it.F;
      temp = it.S;
      farzi.pb({tp, temp});
    }
    reverse(all(farzi));
    for (auto it : farzi) {
      // debug(it.F);
      // out(it.S);
    }
    cout << ans << endl;
  }
 
  return 0;
}
