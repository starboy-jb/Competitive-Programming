/*input
2
7
3 2 3 4
0
3 5 6 7
0
0
0
0
2
5 7
2 7
7
3 2 3 4
0
3 5 6 7
0
0
0
0
2
5 7
2 7
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
 
const int N = 2e3 + 5;
const int logN = log2(N);
vector<int> adj[N];
int up[N][logN + 1];
int tin[N], tout[N], timer = 0;
int level[N];
bool vis[N];

void dfs(int s, int p) {
  vis[s] = true;
  tin[s] = ++timer;

  up[s][0] = p;

  for (int i = 1; i <= logN; i++) {
    up[s][i] = up[up[s][i - 1]][i - 1];
  }

  for (auto it : adj[s]) {
    if (!vis[it]) {
      level[it] = level[s] + 1;
      dfs(it, s);
    }
  }

  tout[s] = ++timer;
}

bool is_ancestor(int u, int v) {
  return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int lca(int u, int v) {
  if (is_ancestor(u, v))
    return u;
  if (is_ancestor(v, u))
    return v;

  for (int i = logN; i >= 0; i--) {
    if (!is_ancestor(up[u][i], v))
      u = up[u][i];
  }
  return up[u][0];
}

void init(int n) {
  timer = 0;
  for (int i = 1; i <= n; i++) {
    adj[i].clear();
    vis[i] = false;
  }
}
 
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
 
  int test;
  cin >> test;
  int ntest = 1;
  while (test--) {
    int n;
    cin >> n;
    init(n);
    for (int i = 1; i <= n; i++) {
      int m;
      cin >> m;
      int v;
      int u = i;
      while (m--) {
        cin >> v;
        adj[u].pb(v);
        adj[v].pb(u);
      }
    }
    dfs(1, 1);
    int q;
    cin >> q;
    cout << "Case " << ntest++ << ":" << endl;
    while (q--) {
      int u, v;
      cin >> u >> v;
      int ans = lca(u, v);
      cout << ans << endl;
    }
  }
 
  return 0;
} 
