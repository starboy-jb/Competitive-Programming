/*input
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef pair<ll , ll> PLL;
typedef long double ld;

#define pb push_back
#define all(c) c.begin(),c.end()
#define allr(c) c.rbegin(),c.rend()
#define mod 1000000007
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

#define out(container) cout << #container << " = "; for (auto it : container) cout << it << " "; cout << endl;


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

const int N = 1e5 + 1;

int seg[4 * N];
bool lazy[4 * N];

void update(int l, int r, int low, int high, int pos) {
  if (low > high)
    return;
  
  if (lazy[pos]) {
    seg[pos] = high - low + 1 - seg[pos];
    if (low != high) {
      lazy[2 * pos + 1] = !lazy[2 * pos + 1];
      lazy[2 * pos + 2] = !lazy[2 * pos + 2];
    }
    lazy[pos] = false;
  }

  if (low > r || high < l) {
    return;
  }

  if (low >= l && high <= r) {
    seg[pos] = high - low + 1 - seg[pos];
    if (low != high) {
      lazy[2 * pos + 1] = !lazy[2 * pos + 1];
      lazy[2 * pos + 2] = !lazy[2 * pos + 2];
    }
    return;
  }

  int mid = (low + high) >> 1;
  update(l, r, low, mid, 2 * pos + 1);
  update(l, r, mid + 1, high, 2 * pos + 2);
  seg[pos] = seg[2 * pos + 1] + seg[2 * pos + 2];
}

int query(int l, int r, int low, int high, int pos) {
  if (low > high)
    return 0;

  if (lazy[pos]) {
    seg[pos] = high - low + 1 - seg[pos];
    if (low != high) {
      lazy[2 * pos + 1] = !lazy[2 * pos + 1];
      lazy[2 * pos + 2] = !lazy[2 * pos + 2];
    }
    lazy[pos] = false;
  }

  if (low > r || high < l) {
    return 0;
  }

  if (low >= l && high <= r) {
    return seg[pos];
  }

  int mid = (low + high) >> 1;
  int ans1 = query(l, r, low, mid, 2 * pos + 1);
  int ans2 = query(l, r, mid + 1, high, 2 * pos + 2);
  return ans1 + ans2;
}


int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
    
  int n, m;
  cin >> n >> m;
  while (m--) {
    int type, l, r;
    cin >> type >> l >> r;
    l--;
    r--;
    if (type == 0) {
      update(l, r, 0, n - 1, 0);
    }
    else {
      cout << query(l, r, 0, n - 1, 0) << endl;
    }
  }

  return 0;
}
