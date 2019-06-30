/*input
6
4 0
BAAB
4 1
BAAB
4 1
ABBA
5 2
BBBBB
15 3
ABBBABBBBBABABB
50 4
BBABAABBBBABBBBAABBBBAABBBBBABBBAABABBBBBBABABBAAB

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

// #warning size
const int N = 1e6 + 1;
int pw[N];
void pre() {
  pw[0] = 1;
  for (int i = 1; i < N; i++) {
    pw[i] = mul(pw[i - 1], 2);
  }
}
int n, k;
string str;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);  

  freopen("in", "r", stdin);
  freopen("out", "w", stdout);

  pre();
  int t;
  cin >> t;
  for (int test = 1; test <= t; test++) {
    cin >> n >> k;
    cin >> str;
    vector <int> vec;
    int ans = 0;
    if (k == 0) {
      for (int i = 0; i < n; i++) {
        if (str[i] == 'B') {
          ans = add(ans, pw[i + 1]);
        }
      }
      cout << "Case #" << test << ": " << ans << endl;
      continue;
    }
    int a = 0, b = 0;
    bool ok = false;
    for (int i = n - 1; i >= 0; i--) {
      if (str[i] == 'B') {
        ok = true;
      }
      if (!ok) {
        continue;
      }
      a += (str[i] == 'A');
      b += (str[i] == 'B');
      if (abs(a - b) > k && b > a + k) {
        //trace(i, a, b);
        str[i] = 'A';
        b--;
        a++;
        ans = add(ans, pw[i + 1]);
      }
      if (a >= b) {
        ok = false;
        a = 0;
        b = 0;
      }
    }

    cout << "Case #" << test << ": " << ans << endl;
  }

  return 0;
}
