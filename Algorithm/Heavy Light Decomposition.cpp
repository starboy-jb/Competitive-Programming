/*input
2
 
4
1 2 1
2 3 2
2 4 8
QUERY 1 2
CHANGE 1 3
QUERY 1 2
QUERY 1 1
QUERY 3 4
DONE
 
3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE
 
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
 
const int N = 1e4 + 5;
const int LG = log2(N) + 1;
 
 
// segment tree
 
int seg[4 * N + 5];
 
void update(int low, int high, int ind, int value, int pos) {
  if (low == high) {
    seg[pos] = value;
    return;
  }
 
  int mid = (low + high) >> 1;
 
  if (ind <= mid)
    update(low, mid, ind, value, 2 * pos + 1);
  else
    update(mid + 1, high, ind, value, 2 * pos + 2);
 
  seg[pos] = max(seg[2 * pos + 1], seg[2 * pos + 2]);
}
 
int query(int low, int high, int l, int r, int pos) {
  if (low > r || high < l) return -inf;
  if (low >= l && high <= r) return seg[pos];
 
  int mid = (low + high) >> 1;
 
  return max(query(low, mid, l, r, 2 * pos + 1), query(mid + 1, high, l, r, 2 * pos + 2));
}
 
vector<int> adj[N];
 
int sub_size[N], par[N][LG], tin[N], tout[N];
 
int timer = 0;
 
// preprocess
 
void dfs(int s, int p) {
  tin[s] = ++timer;
 
  sub_size[s] = 1;
 
  par[s][0] = p;
 
  for (int i = 1; i < LG; i++)
    par[s][i] = par[par[s][i - 1]][i - 1];
 
  for (auto it : adj[s]) {
    if (it == p) continue;
    dfs(it, s);
 
    sub_size[s] += sub_size[it];
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
 
  for (int i = LG - 1; i >= 0; i--) {
    if (!is_ancestor(par[u][i], v))
      u = par[u][i];
  }
 
  return par[u][0];
}
 
int heavy[N];
 
void dfs1(int s, int p) {
  int max_c_size = 0;
 
  for (auto it : adj[s]) {
    if (it == p) continue;
 
    dfs1(it, s);
 
    if (sub_size[it] > max_c_size)
      max_c_size = sub_size[it], heavy[s] = it;
  }
}
 
// HLD
 
int pos[N], head[N];
int cur_pos = 0;
 
void decompose(int s, int p) {
  pos[s] = cur_pos++, head[s] = p;
 
  if (heavy[s] != -1)
    decompose(heavy[s], p);
 
  for (auto it : adj[s]) {
    if (it == par[s][0] || it == heavy[s]) continue;
    decompose(it, it);
  }
}
 
int query(int l, int r) {
  if (l > r)
    return 0;
  return query(0, N - 1, l, r, 0);
}
 
void update(int u, int w) {
  update(0, N - 1, pos[u], w, 0);
}
 
 
int query_up(int u, int v) {
  // u -> v, where v is ancestor
  int ans = 0;
  while (head[u] != head[v]) {
    int cur = query(pos[head[u]], pos[u]);
    ans = max(ans, cur);
    u = par[head[u]][0];
  }
  int cur = query(pos[v] + 1, pos[u]);
  ans = max(ans, cur);
  return ans;
}
 
// max edge weight between two edge
int query1(int u, int v) {
  int l = lca(u, v);
  int ans = max(query_up(u, l), query_up(v, l));
  return ans;
}
 
void init() {
  for (int i = 0; i < N; i++) {
    adj[i].clear();
    heavy[i] = -1;
  }
  timer = 0;
  cur_pos = 0;
}
 
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int test;
  cin >> test;
  while (test--) {
    init();
    int n;
    cin >> n;
    vector<array<int, 3>> edges;
    int u, v, w;
 
    for (int i = 0; i < n - 1; i++) {
      cin >> u >> v >> w;
      edges.push_back({u, v, w});
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
 
    dfs(1, 1);
    dfs1(1, 1);
    decompose(1, 1);
 
    for (auto it : edges) {
      u = it[0], v = it[1], w = it[2];
      if (par[v][0] != u)
        swap(u, v);
 
      update(v, w);
    }
 
    while (1) {
      string type;
      cin >> type;
 
      if (type[0] == 'D')
        break;
 
      if (type[0] == 'C') {
        int ind;
        cin >> ind >> w;
        ind--;
        u = edges[ind][0], v = edges[ind][1];
        if (par[v][0] != u)
          swap(u, v);
 
        update(v, w);
      } else {
        cin >> u >> v;
        int ans = query1(u, v);
        cout << ans << endl;
      }
    }
  }
 
  return 0;
} 
