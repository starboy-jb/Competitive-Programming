/*input
1
5 5
1 4
4 5
1 3
3 2
2 1

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

vector <int> adj[N], revAdj[N];
bool vis[N];
stack <int> stck;
int noc = 0;

void dfs (int s) {
  vis[s] = true;
  for (auto it : adj[s]) {
    if (!vis[it]) {
      dfs(it);
    }
  }
  stck.push(s);
}

void reverseGraph(int n) {
  for (int i = 1; i <= n; ++i) {
    for (auto it : adj[i]) {
      revAdj[it].pb(i);
    }
  }
}

void printSCC (int s) {
  vis[s] = true;
  // cout << s << " ";
  for (auto it : revAdj[s]) {
    if (!vis[it]) {
      printSCC(it);
    }
  }
}

void Kosaraju () {
  memset(vis, false, sizeof(vis));
  while (!stck.empty()) {
    int tp = stck.top();
    stck.pop();
    if (!vis[tp]) {
      noc++;
      printSCC(tp);
      // cout << endl;
    }
  }
}

void init(int n) {
  for (int i = 1; i <= n; i++) {
    vis[i] = false;
    adj[i].clear();
    revAdj[i].clear();
  }
  noc = 0;
}


int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int test;
  cin >> test;
  while (test--) {
    int n, m;
    cin >> n >> m;
    int u, v;
    for (int i = 0; i < m; i++) {
      cin >> u >> v;
      adj[u].pb(v);
    }
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        dfs(i);
      }
    }
    reverseGraph(n);
    Kosaraju();
    cout << noc - 1 << endl;
  }

  return 0;
}
