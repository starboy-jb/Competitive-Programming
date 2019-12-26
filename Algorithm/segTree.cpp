/*input
1
8 6
0 2 4 26
0 4 8 80
0 4 5 20
1 8 8 
0 5 7 14
1 4 8
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

struct data {
  // Use required attributes
 
  ll sum;
 
  // Default Values
  data() : sum(0) {};
};
 
struct SegTree {
  int N;
  vector<data> seg;
  vector<bool> cLazy;
  vector<ll> lazy;
 
  void init(int n) {
    N = n;
    seg.resize(4 * N + 5);
    cLazy.assign(4 * N + 5, false);
    lazy.assign(4 * N + 5, 0);
  }
 
  // Write reqd merge functions
  void merge(data &cur, data &l, data &r) {
    cur.sum = l.sum + r.sum;
  }
 
  // Handle lazy propagation appriopriately
  void propagate(int node, int L, int R) {
    if (L != R) {
      cLazy[node * 2] = 1;
      cLazy[node * 2 + 1] = 1;
      lazy[node * 2] += lazy[node];
      lazy[node * 2 + 1] += lazy[node];
    }
    seg[node].sum += (R - L + 1) * lazy[node];
    lazy[node] = 0;
    cLazy[node] = 0;
  }
 
  void build(int node, int L, int R) {
    if (L == R) {
      return;
    }
    int M = (L + R) / 2;
    build(node * 2, L, M);
    build(node * 2 + 1, M + 1, R);
    merge(seg[node], seg[node * 2], seg[node * 2 + 1]);
  }
 
  data Query(int node, int L, int R, int i, int j) {
    if (cLazy[node])
      propagate(node, L, R);
    if (j < L || i > R)
      return data();
    if (i <= L && R <= j)
      return seg[node];
    int M = (L + R) / 2;
    data left = Query(node * 2, L, M, i, j);
    data right = Query(node * 2 + 1, M + 1, R, i, j);
    data cur;
    merge(cur, left, right);
    return cur;
  }
 
  data pQuery(int node, int L, int R, int pos) {
    if (cLazy[node])
      propagate(node, L, R);
    if (L == R)
      return seg[node];
    int M = (L + R) / 2;
    if (pos <= M)
      return pQuery(node * 2, L, M, pos);
    else
      return pQuery(node * 2 + 1, M + 1, R, pos);
  }
 
  void Update(int node, int L, int R, int i, int j, int val) {
    if (cLazy[node])
      propagate(node, L, R);
    if (j < L || i > R)
      return;
    if (i <= L && R <= j) {
      cLazy[node] = 1;
      lazy[node] = val;
      propagate(node, L, R);
      return;
    }
    int M = (L + R) / 2;
    Update(node * 2, L, M, i, j, val);
    Update(node * 2 + 1, M + 1, R, i, j, val);
    merge(seg[node], seg[node * 2], seg[node * 2 + 1]);
  }
 
  void pUpdate(int node, int L, int R, int pos, int val) {
    if (cLazy[node])
      propagate(node, L, R);
    if (L == R) {
      cLazy[node] = 1;
      lazy[node] += val;
      propagate(node, L, R);
      return;
    }
    int M = (L + R) / 2;
    if (pos <= M)
      pUpdate(node * 2, L, M, pos, val);
    else
      pUpdate(node * 2 + 1, M + 1, R, pos, val);
    merge(seg[node], seg[node * 2], seg[node * 2 + 1]);
  }
 
  data query(int pos) { return pQuery(1, 1, N, pos); }
 
  data query(int l, int r) { return Query(1, 1, N, l, r); }
 
  void update(int pos, int val) { pUpdate(1, 1, N, pos, val); }
 
  void update(int l, int r, int val) { Update(1, 1, N, l, r, val); }
};

int main()
{
  ios_base::sync_with_stdio(false); // 🏁 👀 💕
  cin.tie(NULL);
  
  int test;
  cin >> test;
  while (test--) {
    int n, q;
    cin >> n >> q;
    SegTree obj;
    obj.init(n + 5);
    while (q--) {
      int type;
      cin >> type;
      if (!type) {
        int l, r, v;
        cin >> l >> r >> v;
        obj.update(l, r, v);
      } else {
        int l, r;
        cin >> l >> r;
        ll ans = obj.query(l, r).sum;
        cout << ans << endl;
      }
    }
  }

  return 0;
}
