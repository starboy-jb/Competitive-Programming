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

const int N = 1e6 + 5;
ll seg[4 * N], lazy[4 * N];

void propagate(int pos, int low, int high) {
  if (low != high) {
    lazy[2 * pos + 1] += lazy[pos];
    lazy[2 * pos + 2] += lazy[pos];
  }
  lazy[pos] = 0;
}

void merge(int pos) {
  seg[pos] = seg[2 * pos + 1] + seg[2 * pos + 2];
}

void update(int low, int high, int l, int r, ll v, int pos) {
  if (lazy[pos]) {
    seg[pos] += (high - low + 1) * lazy[pos];
    propagate(pos, low, high);
  }
  if (l > r || low > r || high < l) return;
  if (low >= l && high <= r) {
    seg[pos] += (high - low + 1) * v;
    if (low != high) {
      lazy[2 * pos + 1] += v;
      lazy[2 * pos + 2] += v;
    }
    return;
  } else {
    int mid = (low + high) >> 1;
    update(low, mid, l, r, v, 2 * pos + 1);
    update(mid + 1, high, l, r, v, 2 * pos + 2);
    merge(pos);
  }
}
ll query(int low, int high, int l, int r, int pos) {
  if (lazy[pos]) {
    seg[pos] += (high - low + 1) * lazy[pos];
    propagate(pos, low, high);
  }
  if (l > r || low > r || high < l) return 0;
  if (l <= low && high <= r) {
    return seg[pos];
  }
  int mid = (low + high) >> 1;
  return query(low, mid, l, r, 2 * pos + 1) 
         + query(mid + 1, high, l, r, 2 * pos + 2);
}

void init() {
  memset(seg, 0, sizeof(seg));
  memset(lazy, 0, sizeof(lazy));
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int test;
  cin >> test;
  while (test--) {
    int n, q;
    cin >> n >> q;
    while (q--) {
      int type;
      cin >> type;
      if (!type) {
        int l, r, v;
        cin >> l >> r >> v;
        l--;
        r--;
        update(0, n - 1, l, r, v, 0);
      } else {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        ll ans = query(0, n - 1, l, r, 0);
        cout << ans << endl;
      }
    }
    init();
  }

  return 0;
}
