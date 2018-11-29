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

vector <int> adj[MAX];
int dp[MAX][2];

int vertexCover (int s, int parent, int status) {
    if (dp[s][status] != -1) {
        return dp[s][status];
    }
    int ans = 0;
    dp[s][status] = 1;
    for (auto it : adj[s]) {
        if (it == parent) continue;
        if (status == 1) {
            ans = ans + min(vertexCover(it, s, 0) , vertexCover(it, s, 1));
        }
        else {
            ans = ans + vertexCover(it, s, 1);
        }
    }
    ans = ans + status;
    dp[s][status] = ans;
    return ans;
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
        --u;
        --v;
        adj[u].pb(v);
        adj[v].pb(u);
        dp[i][0] = -1;
        dp[i][1] = -1;
    }
    dp[n - 1][0] = -1;
    dp[n - 1][1] = -1;

    cout << min(vertexCover(0, 0, 0), vertexCover(0, 0, 1)) << endl;


    return 0;
}
