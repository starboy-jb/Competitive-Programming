/*input
5 4
1 2
2 3
2 4
4 5
2 1
2 5
1 2
2 5


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
#include <fstream>
#include <stack>

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

const int N = 1e5 + 5;
const int LOG_N = log2(N) + 1;

set<int> adj[N];

int subtree[N], par[N];

int nodes = 0;

void dfs(int s, int p) {
  nodes++;
  subtree[s] = 1;

  for (auto it : adj[s]) {
    if (it == p) continue;
    dfs(it, s);
    subtree[s] += subtree[it];
  }
}


int centroid(int s, int p) {
  for (auto it : adj[s]) {
    if (it == p) continue;

    if (subtree[it] > nodes / 2)
      return centroid(it, s);
  }

  return s;
}

void decompose(int s, int p) {
  nodes = 0;
  dfs(s, s);
  int c = centroid(s, s);
  if (p == -1)
    p = c;

  par[c] = p;

  for (auto it : adj[c]) {
    adj[it].erase(c);
    decompose(it, c);
  }
}


int tin[N], tout[N], dis[N], timer = 0;
int up[N][LOG_N];

void dfs_original(int s, int p) {
  tin[s] = ++timer;

  up[s][0] = p;

  for (int i = 1; i < LOG_N; i++)
    up[s][i] = up[up[s][i - 1]][i - 1];

  for (auto it : adj[s]) {
    if (it == p) continue;
    dis[it] = dis[s] + 1;
    dfs_original(it, s);
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

  for (int i = LOG_N - 1; i >= 0; i--) {
    if (!is_ancestor(up[u][i], v))
      u = up[u][i];
  }

  return up[u][0];
}

int get_dis(int u, int v) {
  int l = lca(u, v);
  int ans = dis[u] + dis[v] - 2 * dis[l];
  return ans;
}

int mn[N];

void update(int node) {
  int p = node;
  while (1) {
    mn[p] = min(mn[p], get_dis(p, node));
    if (p == par[p])
      break;
    p = par[p];
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n, q;
  cin >> n >> q;

  int u, v;

  for (int i = 0; i < n - 1; i++) {
    cin >> u >> v;
    adj[u].insert(v);
    adj[v].insert(u);
  }

  dfs_original(1, 1);

  decompose(1, -1);

  for (int i = 1; i < N; i++)
    mn[i] = inf;

  update(1);

  while (q--) {
    int type, node;
    cin >> type >> node;

    if (type == 1) { // paint
      update(node);
    } else {
      int p = node, ans = inf;
      while (1) {
        ans = min(ans, mn[p] + get_dis(p, node));
        if (p == par[p])
          break;
        p = par[p]; 
      }
      cout << ans << endl;
    }
  }

  return 0;
}
