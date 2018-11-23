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
#define MAX 100001

struct Edge {
    int src;
    int dest;
    int weight;
}graph[MAX];

int dist[MAX];

void BellmanFord (int n , int m , int s) {
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }
    dist[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            int u = graph[j].src;
            int v = graph[j].dest;
            int w = graph[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = w + dist[u];
            }
        }
    }
    for (int j = 0; j < m; j++) {
        int u = graph[j].src;
        int v = graph[j].dest;
        int w = graph[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "Graph contain a negative cycle" << endl;
            return;
        }
    }
}

void print(int n, int m) {
    for (int i = 0; i < n; i++) {
        cout << "distance from source to " << i << " is " << dist[i] << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n , m;
    cin >> n >> m;
    int src , dest , w;
    for (int i = 0; i < m; i++) {
        cin >> src >> dest >> w;
        graph[i].src = src;
        graph[i].dest = dest;
        graph[i].weight = w;
    }
    BellmanFord(n , m , 0);
    print(n , m);

    return 0;
}
