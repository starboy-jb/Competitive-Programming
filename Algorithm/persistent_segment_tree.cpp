/*input
10
1 2 3 4 5 6 7 8 9 10 
6
2 0 1 6
1 0 10 30
1 1 2 10
1 2 3 10
2 3 2 3
2 1 1 10
 
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

int seg[4 * LOG_N * N], lc[4 * LOG_N * N], rc[4 * LOG_N * N], root[N];
int id = 0;

int build(int low, int high) {
  int node = id++;
  if (low == high) {
    return node;
  }

  int mid = (low + high) >> 1;

  lc[node] = build(low, mid);
  rc[node] = build(mid + 1, high);

  return node;
}

int update(int prev, int low, int high, int pos, int value) {
  int node = id++;
  if (low == high) {
    seg[node] = value;
    return node;
  }

  lc[node] = lc[prev];
  rc[node] = rc[prev];

  int mid = (low + high) >> 1;

  if (pos <= mid) {
    lc[node] = update(lc[prev], low, mid, pos, value);
  } else {
    rc[node] = update(rc[prev], mid + 1, high, pos, value);
  }

  seg[node] = seg[lc[node]] + seg[rc[node]];

  return node;
}

int query(int root, int low, int high, int l, int r) {
  if (low > r || high < l) return 0;
  if (low >= l && high <= r) return seg[root];
 
  int mid = (low + high) >> 1;
 
  return query(lc[root], low, mid, l, r) + query(rc[root], mid + 1, high, l, r);
}

void persistentSegTree(int n) {
  root[0] = build(0, n - 1);
}

 
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n;
  cin >> n;
  vector<int> vec;
  int v;
  for (int i = 0; i < n; i++) {
    cin >> v;
    vec.pb(v);
  }
  
  int q;
  cin >> q;

  persistentSegTree(n);

  for (int i = 0; i < n; i++) {
    root[0] = update(root[0], 0, n - 1, i, vec[i]);
  }
 
  int first_type = 1;
 
  while (q--) {
    int type;
    cin >> type;
 
    if (type == 1) {
      int idx, pos, v;
      cin >> idx >> pos >> v;
      pos--;
      v += query(root[idx], 0, n - 1, pos, pos);
      root[first_type++] = update(root[idx], 0, n - 1, pos, v);
    } else {
      int idx, l, r;
      cin >> idx >> l >> r;
      l--, r--;
      int ans = query(root[idx], 0, n - 1, l, r);
      cout << ans << endl;
    }
  }
 
  return 0;
} 
