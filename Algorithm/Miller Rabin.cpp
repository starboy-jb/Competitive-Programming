/*input
6
2
3
4
5
6
941

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using u64 = uint64_t;
using u128 = __uint128_t;

u64 powr(u64 a, u64 b, u64 mod) {
  u64 x = 1;
  while (b) {
    if (b & 1)
      x = (u128)x * a % mod;
    a = (u128)a * a % mod;
    b >>= 1;
  }
  return x;
}

bool check_composite(u64 n, int a, u64 d, int s) {
  u64 x = powr(a, d, n);
  if (x == 1 || x == n - 1)
    return false;

  for (int r = 1; r < s; r++) {
    x = (u128)x * x % n;

    if (x == n - 1)
      return false;
  }

  return true;
}

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

bool MillerRabin(u64 n) {
  if (n < 4)
    return (n == 2 || n == 3);

  for (auto it : primes) {
    if (n == it)
      return true;

    if (n % it == 0)
      return false;
  }

  int s = 0;
  u64 d = n - 1;

  while (d % 2 == 0) {
    d >>= 1;
    s++;
  }

  for (auto a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (check_composite(n, a, d, s))
      return false;
  }

  return true;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int test;
  cin >> test;
  while (test--) {
    u64 n;
    cin >> n;
    cout << (MillerRabin(n) ? "YES" : "NO") << endl;
  }

  return 0;
}
