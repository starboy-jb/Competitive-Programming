/*input
9
1 2
1 3
2 4
2 5
5 8
5 9
3 6
3 7
3
6 7
6 9
4 9


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
int mod = 100000000;
#define PI 3.14159265
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl;
#define MAX 2001

template < typename T > T GCD(T a, T b)            { ll t; while(a) { t = a; a = b % a; b = t; } return b; }
template < typename T > string toString(T a)       { return to_string(a); }
template < typename T > void toInt(string s, T &x) { stringstream str(s); str >> x;}
inline int add(ll a, ll b) {a += b; if (a < 0) a += mod; return a;}
inline int sub(ll a, ll b) {a -= b; if (a < 0) a += mod; return a;}
inline int mul(ll a, ll b) {return (a * 1ll * b) % mod;}
inline int pwr(ll x, ll y) {
    int ans = 1 % mod;
    while (y) {
        if (y & 1) ans = mul(ans, x);
        x = mul(x, x);
        y >>= 1;
    }
    return ans;
}
inline int inv(int a) {return pwr(a, mod - 2);}

vector <int> adj[MAX];
int level[MAX], firstIndex[MAX];
vector <int> eulerTour;
bool vis[MAX];

void dfs(int s) {
    vis[s] = true;
    for (auto it : adj[s]) {
        if (!vis[it]) {
            level[it] = level[s] + 1;
            eulerTour.pb(s);
            if (firstIndex[s] == -1) firstIndex[s] = eulerTour.size() - 1;
            dfs(it);
            eulerTour.pb(it);
            if (firstIndex[it] == -1) firstIndex[it] = eulerTour.size() - 1;
        }
    }
}

struct SegTree {
    int seg[4 * MAX];

    void build(int l, int r, int pos) {
        if (l == r) {
            seg[pos] = l;
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, 2 * pos + 1);
        build(mid + 1, r, 2 * pos + 2);
        if (level[eulerTour[seg[2 * pos + 1]]] < level[eulerTour[seg[2 * pos + 2]]]) {
            seg[pos] = seg[2 * pos + 1];
        } else {
            seg[pos] = seg[2 * pos + 2];
        }
    }

    int query(int ql, int qr, int l, int r, int pos) {
        if (l >= ql && r <= qr) {
            return seg[pos];
        }
        if (r < ql || l > qr) {
            return -1;
        }
        int mid = (l + r) / 2;
        int u = query(ql, qr, l, mid, 2 * pos + 1);
        int v = query(ql, qr, mid + 1, r, 2 * pos + 2);
        if (u == -1) return v;
        if (v == -1) return u;
        return (level[eulerTour[u]] < level[eulerTour[v]]? u: v);
    }
    int lca(int, int);
};

int SegTree :: lca(int ind1, int ind2) {
    int ans = query(ind1, ind2, 0, eulerTour.size() - 1, 0);
    return eulerTour[ans];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int u, v;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    memset(firstIndex, -1, sizeof(firstIndex));
    level[1] = 0;
    dfs(1);
    eulerTour.pb(1);
    if (firstIndex[1] == -1) firstIndex[1] = 0;
    SegTree seg;
    seg.build(0, eulerTour.size() - 1, 0);
    int q;
    cin >> q;
    while (q--) {
        cin >> u >> v;
        if (firstIndex[u] > firstIndex[v]) swap(u, v);
        int ans = seg.lca(firstIndex[u], firstIndex[v]);
        cout << ans << endl;
    }


    return 0;
}
