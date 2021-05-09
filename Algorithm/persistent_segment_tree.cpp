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

struct Node {
  Node *left, *right;
  int sum;
  Node() : left(NULL), right(NULL), sum(0) {}
  Node(int v) : left(NULL), right(NULL), sum(v) {}
};

Node* merge(Node *node1, Node *node2) {
  Node *node = new Node();
  node->left = node1;
  node->right = node2;
  if (node1) node->sum += node1->sum;
  if (node2) node->sum += node2->sum;
  return node;
}

Node* build(vector<int>& vec, int low, int high) {
  if (low == high) {
    return new Node(vec[low]);
  }
  int mid = (low + high) >> 1;
  Node *root = merge(build(vec, low, mid), build(vec, mid + 1, high));
  return root;
}

Node* update(Node *root, int low, int high, int pos, int value) {
  if (low == high) {
    return new Node(value);
  }
  int mid = (low + high) >> 1;
  if (pos <= mid) {
    return merge(update(root -> left, low, mid, pos, value), root -> right);
  } else {
    return merge(root -> left, update(root -> right, mid + 1, high, pos, value));
  }
  return root;
}

int query(Node *root, int low, int high, int l, int r) {
  if (low > r || high < l) return 0;
  if (low >= l && high <= r) return root -> sum;

  int mid = (low + high) >> 1;

  int left = query(root -> left, low, mid, l, r);
  int right = query(root -> right, mid + 1, high, l, r);
  return left + right;
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

  Node *root;
  vector<Node*> version(q);

  version[0] = build(vec, 0, n - 1);

  int first_type = 1;

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int idx, pos, v;
      cin >> idx >> pos >> v;
      pos--;
      v += query(version[idx], 0, n - 1, pos, pos);
      version[first_type++] = update(version[idx], 0, n - 1, pos, v);
    } else {
      int idx, l, r;
      cin >> idx >> l >> r;
      l--, r--;
      int ans = query(version[idx], 0, n - 1, l, r);
      cout << ans << endl;
    }
  }

  return 0;
}
