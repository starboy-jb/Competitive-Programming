/*input
7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3
 
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
int arr[N];
 
vector<int> seg[4 * N];
 
void build(int low, int high, int pos) {
  if (low == high) {
    seg[pos].push_back(arr[low]);
    return;
  }
 
  int mid = (low + high) >> 1;
 
  build(low, mid, 2 * pos + 1);
  build(mid + 1, high, 2 * pos + 2);
 
  merge(all(seg[2 * pos + 1]), all(seg[2 * pos + 2]), back_inserter(seg[pos]));
}
 
int query(int low, int high, int l, int r, int w, int pos) {
  if (low > r || high < l) return 0;
 
  if (low >= l && high <= r) {
    int ind = upper_bound(all(seg[pos]), w) - seg[pos].begin();
    return ind;
  }
 
  int mid = (low + high) >> 1;
 
  return query(low, mid, l, r, w, 2 * pos + 1) + query(mid + 1, high, l, r, w, 2 * pos + 2);
}
 
int get_count(int n, int l, int r, int w) {
  int ans = query(0, n - 1, l, r, w, 0);
  return ans;
}
 
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n, q;
  cin >> n >> q;
  vector<PII> vec;
  int v, u;
  for (int i = 0; i < n; i++) {
    cin >> v;
    vec.pb({v, i + 1});
  }
 
  sort(all(vec));
 
  v = 1;
 
  vector<int> mapped_value(N);
 
  for (auto it : vec) {
    mapped_value[v] = it.F;
    arr[it.S - 1] = v++;
  }
 
  build(0, n - 1, 0);
 
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
 
    l--, r--;
 
    int ans = 0, low = 1, high = N - 1, mid;
 
    while (low <= high) {
      mid = low + (high - low) / 2;
      int cur = get_count(n, l, r, mid);
       
      if (cur >= k) {
        ans = mid;
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
 
    ans = mapped_value[ans];
 
    cout << ans << endl;
  }
 
  return 0;
}  
