#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> PII;
typedef double ld;

#define pb push_back
#define all(c) c.begin(),c.end()
#define allr(c) c.rbegin(),c.rend()
#define MOD 1000000007
#define PI 3.14159265

int capacity[202][202];
vector<int> adj[202];
int nd , e;
int source , sink;
int parent[202];

bool bfs() {
    bool visited[nd];
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

    int n;
    cin >> n;
    vector<PII> vec1 , vec2;
    int v;
    int x , y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        vec1.pb({x , y});
    }
    int m = n;
     for (int i = 0; i < n; i++) {
        cin >> x >> y;
        vec2.pb({x , y});
    }
    for (int i = 0; i < n; i++) {
        adj[0].pb(i + 1);
        capacity[0][i + 1] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vec1[i].first < vec2[j].first && vec1[i].second < vec2[j].second) {
                adj[i + 1].pb(n + j + 1);
                capacity[i + 1][n + j + 1] = 1;
            }
            adj[n + j + 1].pb(m + n + 1);
            capacity[n + j + 1][m + n + 1] = 1;
        }
    }
    nd = m + n + 2;
    source = 0;
    sink = n + m + 1;

    int flow = 0, max_flow = 0;
    int u;

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
