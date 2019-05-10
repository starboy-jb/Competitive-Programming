#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef pair<ll , ll> PLL;
typedef double ld;

#define pb push_back
#define all(c) c.begin(),c.end()
#define allr(c) c.rbegin(),c.rend()
#define MOD 1000000007
#define PI 3.14159265

#define MAX 100001

struct Point{
    int x;
    int y;
};

bool onSegment(Point p , Point r , Point q) {

    if (r.x >= min(p.x , q.x) && r.y >= min(p.y , q.y) && r.x <= max(p.x , q.x) && r.y <= max(p.y , q.y)) {
        return true;
    }
    else return false;
}

int orientation(Point p , Point q , Point r) {
    int o = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (o == 0) {
        return 0;
    }
    return (o > 0 ? 1 : 2);
}

bool doIntersect(Point p1 , Point q1 , Point p2 , Point q2) {
    int o1 = orientation(p1 , q1 , p2);
    int o2 = orientation(p1 , q1 , q2);
    int o3 = orientation(p2 , q2 , p1);
    int o4 = orientation(p2 , q2 , q1);

    if (o1 != o2 && o3 != o4) {
        return true;
    }
    if (onSegment(p1 , p2 , q1)) return true;
    if (onSegment(p1 , q2 , q1)) return true;
    if (onSegment(p2 , p1 , q2)) return true;
    if (onSegment(p2 , q1 , q2)) return true;

    return false;
}
void arrange() {

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    

    return 0;
}
