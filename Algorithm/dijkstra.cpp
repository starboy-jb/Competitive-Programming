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
int mod = 1000000007;
#define PI 3.14159265
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl;
#define MAX 100001

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

vector <PII> adj[MAX];
vector <ll> cost(MAX);
bool vis[MAX];
int par[MAX];

void dijkstra(int s, int n) {
    priority_queue<PII, vector <PII>, greater<PII> > pq;
    fill(all(cost), (ll)1e12);
    pq.push({1, s});
    vis[s] = true;
    cost[1] = 0;
    par[1] = 1;
    while (!pq.empty()) {
        s = pq.top().second;
        ll w = pq.top().first;
        pq.pop();
        vis[s] = true;
        for (auto it : adj[s]) {
            if (!vis[it.first] && w + it.second < cost[it.first]) {
                cost[it.first] = w + it.second;
                pq.push({cost[it.first], it.first});
                par[it.first] = s;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    dijkstra(1, n);

    return 0;
}
