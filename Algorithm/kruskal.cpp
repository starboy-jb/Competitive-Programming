/*input
1
2
5
7
1 2 1
2 3 2
2 4 6
5 2 1
5 1 3
4 5 2
3 4 3

*/
 
/*
                                                    ______________
                                                          |       )
                                                          |   )   /
                                                          |______/
                                                    |     |      \
                                                    |     |   )   \
                                                    |_____|_______)
 
*/
 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <queue>
#include <bitset>
#include <iomanip>
 
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
const int inf = 1034567891;
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

const int N = 1e3 + 5;
int par[N], sz[N];
vector <pair<int, PII> > edges;

int getPar(int k) {
  while (k != par[k]) {
    par[k] = par[par[k]];
    k = par[k];
  }
  return k;
}

void unite(int u, int v) {
  int par1 = getPar(u), par2 = getPar(v);
  if (par1 == par2) return;
  if (sz[par1] > sz[par2]) swap(par1, par2);
  sz[par2] += sz[par1];
  sz[par1] = 0;
  par[par1] = par[par2];
}

void init(int n) {
  edges.clear();
  for (int i = 1; i <= n; i++) {
    par[i] = i;
    sz[i] = 1;
  }
}

int krushkal() {
  sort(all(edges));
  int ans = 0;
  for (auto it : edges) {
    int u = it.S.F;
    int v = it.S.S;
    int w =  it.F;
    if (getPar(u) != getPar(v)) {
      unite(u, v);
      ans += w;
    }
  }
  return ans;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int test;
  cin >> test;
  while (test--) {
    int p, n, m;
    cin >> p >> n >> m;
    int u, v, w;
    init(n);
    for (int i = 0; i < m; i++) {
      cin >> u >> v >> w;
      edges.pb({w * p, {u, v}});
    }
    int ans = krushkal();
    cout << ans << endl;
  } 

  return 0;
}
