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
#define MOD 1000000007
#define PI 3.14159265
#define endl '\n'
#define MAX 200001

vector <int> adj[MAX] , revAdj[MAX];
bool vis[MAX];
stack <int> stck;

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
    for (int i = 0; i < n; ++i) {
        for (auto it : adj[i]) {
            revAdj[it].pb(i);
        }
    }
}

void printSCC (int s) {
    vis[s] = true;
    cout << s << " ";
    for (auto it : revAdj[s]) {
        if (!vis[it]) {
            printSCC(it);
        }
    }
}

void Kosaraju () {
    memset(vis , false , sizeof(vis));
    while (!stck.empty()) {
        int tp = stck.top();
        stck.pop();
        if (!vis[tp]) {
            printSCC(tp);
            cout << endl;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n , e;
    cin >> n >> e;
    int u , v;
    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        adj[u].pb(v);
    }
    dfs(0);
    reverseGraph(n);
    Kosaraju();

    return 0;
}
