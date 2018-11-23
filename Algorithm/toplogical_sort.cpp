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

std::vector<int> adj[MAX];
bool vis[MAX];
stack <int> st;

void toplogicalSort (int s) {
    vis[s] = true;
    for (auto it : adj[s]) {
        if (!vis[it]) {
            toplogicalSort(it);
        }
    }
    st.push(s);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n , m;
    cin >> n >> m;
    int u , v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        adj[u].pb(v);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            toplogicalSort(i);
        }
    }
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    return 0;
}
