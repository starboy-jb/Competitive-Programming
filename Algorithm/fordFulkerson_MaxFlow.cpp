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
#define MAX 100005

int capacity[202][202];
vector<int> adj[202];
int source , sink;
int parent[202];

bool bfs() {
    bool visited[MAX];
    memset(visited , false , sizeof(visited));

    parent[source] = -1;
    queue<int> qu;
    qu.push(source);
    visited[source] = true;
    int s;

    while (!qu.empty()) {
        s = qu.front();
        qu.pop();

        for (auto it : adj[s]) {
            if (!visited[it] && capacity[s][it] > 0) {
                qu.push(it);
                visited[it] = true;
                parent[it] = s;
            }
        }
    }
    return (visited[sink] == true);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, e;
    cin >> n >> e;
    int u, v;
    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        --u;
        --v;
        adj[u].pb(v);
    }

    source = 0;
    sink = n;

    int flow = 0, max_flow = 0;

    while (bfs()) {
        flow = INT_MAX;
        v = sink;
        while (parent[v] != -1) {
            u = parent[v];
            flow = min(flow , capacity[u][v]);
            v = u;
        }
        v = sink;
        while (parent[v] != -1) {
            u = parent[v];
            capacity[u][v] -= flow;
            capacity[v][u] += flow;
            adj[v].pb(u);
            v = u;
        }
        max_flow += flow;
    }

    cout << max_flow << endl;

    return 0;
}
