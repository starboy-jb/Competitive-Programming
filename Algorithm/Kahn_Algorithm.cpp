/*input
5 5
1 3
2 3
3 4
3 5
5 4
*/
/* Topological Sorting in a Direct Acyclic Graph
   Time Complexity: O(V+E)
*/

#include <iostream>
#include <vector>
#include <queue>

const int N = 100001;
std::vector < int > v[N];
int indegree[N];

void kahn(int n) 
{
    std::queue < int > q;
    for(int i = 1; i <= n; i ++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int d = q.front();
        q.pop();
        std::cout << d << " ";
        for(auto x: v[d]) {
            indegree[x] --;
            if(indegree[x] == 0) {
                q.push(x);
            }
        }
    }
}

int main ()
{
    int n, m;
    std::cin >> n >> m;
    
    for(int i = 0; i < m; i ++) {
        int x, y;
        std::cin >> x >> y;
        v[x].push_back(y);
        indegree[y] ++;
    }

    kahn(n);
    return 0;
}

/* Expected Output
   1 2 3 5 4
*/

