/*input
5 
0 0
0 1
100 45
2 3
9 9

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

struct point {
  int x, y, ind;
};
bool comp(point p1, point p2) {
  return p1.x < p2.x;
}

ld euclidean_distance(point p1, point p2) {
  ld x = p1.x - p2.x;
  ld y = p1.y - p2.y;
  ld ans = x * x + y * y;
  ans = sqrt(ans);
  return ans;
}

int main()
{
  ios_base::sync_with_stdio(false); // 🏁 👀 💕
  cin.tie(NULL);
  
  int n;
  cin >> n;
  int x, y;
  vector <point> vec;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    vec.pb({x, y, i});
  }
  sort(all(vec), comp);
  ld ans = inf;
  set <pair<PII, int> > s;
  s.insert({{vec[0].y, vec[0].x}, vec[0].ind});
  int left = 0;
  int a = 0, b = 0;
  for (int i = 1; i < n; i++) {
    while (left < i && vec[i].x - vec[left].x > ans)
      s.erase({{vec[left].y, vec[left].x}, vec[left++].ind});
    for (auto it = s.lower_bound({{vec[i].y - ans, vec[i].x - ans}, 0}); it != s.end() && vec[i].y + ans >= it -> F.F; it++) {
      ld d = euclidean_distance(point({it -> F.S, it -> F.F, it -> S}), vec[i]);
      if (d < ans) {
        a = it -> S;
        b = vec[i].ind;
        if (a > b) swap(a, b);
        ans = d;
      }
    }
    s.insert({{vec[i].y, vec[i].x}, vec[i].ind});
  }
  cout << a << " " << b << " ";
  cout << fixed << setprecision(6) << ans << endl;

  return 0;
}
