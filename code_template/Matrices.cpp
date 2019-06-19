/*input
4 10
6 1 2 7

*/

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

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

template <typename T>
class Matrix {
public:
  vector < vector <T> > A;
  int r, c;

  Matrix(int r, int c) {
    this -> r = r;
    this -> c = c;
    A.assign(r, vector <T> (c));
  }

  Matrix(int r, int c, T v) {
    this -> r = r;
    this -> c = c;
    A.assign(r, vector <T> (c, v)); 
  }

  Matrix (int n) {
    this -> r = this -> c = n;
    A.assign(n, vector <T> (c, 0));
    for (int i = 0; i < n; i++) {
      A[i][i] = (T)1;
    }
  }

  void display() {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        cout << A[i][j] << " ";
      }
      cout << endl;
    }
  }

  Matrix operator * (Matrix &B) {
    int r1 = r;
    int c1 = c;
    int r2 = B.r;
    int c2 = B.c;

    assert(c1 == r2);

    Matrix <T> C(r1, c2, 0);
    for (int i = 0; i < r1; i++) {
      for (int j = 0; j < c2; j++) {
        for (int k = 0; k < c1; k++) {
          C[i][j] = add(C[i][j], mul(A[i][k], B[k][j]));
        }
      }
    }
    return C;
  }

  Matrix operator + (Matrix &B) {
    assert(r == B.r);
    assert(c == B.c);

    Matrix <T> C(r, c, 0);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        C[i][j] = add(A[i][j], B[i][j]);
      }
    }
    return C;
  }

  Matrix operator - (Matrix &B) {
    assert(r == B.r);
    assert(c == B.c);

    Matrix <T> C(r, c, 0);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        C[i][j] = sub(A[i][j], B[i][j]);
      }
    }
    return C;
  }

  Matrix operator ^ (ll n) {
    Matrix <T> C(r, c);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        C[i][j] = A[i][j];
      }
    }
    Matrix <T> ans(r);

    while (n) {
      if (n & 1) {
        ans = ans * C;
      }
      C = C * C;
      n >>= 1;
    }
    return ans;
  }

  vector <T>& operator [](int i) {
    assert(i < r);
    assert(i >= 0);
    return A[i];
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  Matrix <int> A(4, 4, 1);
  A.display();
  Matrix <int> B(4, 4, 3);
  B.display();
  Matrix <int> C = A ^ 2;
  C.display();

  return 0;
}
