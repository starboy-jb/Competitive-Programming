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
#define debug(x) cout << #x << " = " << x << endl;

#warning set N accordingly

struct DSU {
    int connected;
    int par[N], sz[N];
    DSU(int n) {
        for (int i = 1; i <= n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
        connected = n;
    }
    int getPar(int k) {
        while (k != par[k]) {
            par[k] = par[par[k]];
            k = par[k];
        }
        return k;
    }
    void unite(int u, int v) {
        int par1 = getPar(u), par2 = getPar(v);
        if (par1 == par2) return;
        connected--;
        if (sz[par1] > sz[par2])
            swap(par1, par2);
        sz[par2] += sz[par1];
        sz[par1] = 0;
        par[par1] = par[par2];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);



    return 0;
}
