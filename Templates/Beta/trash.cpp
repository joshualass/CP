#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
struct edge {
    int from, fdx, snk, rdx;
    ll spd;
};
 
int main() {
 
    int n, m;

    cin >> n >> m;
 
    vector<vector<edge> > c(n, vector<edge>());
    vector<vector<edge> > cRev(n, vector<edge>());

    vector<unordered_map<int,ll>> graph(n);
 
    for (int i = 0; i < m; i++) {
        ll spd;
        int from, to; cin >> from >> to >> spd;
        from--; to--;

        graph[from][to] += spd;
        graph[to][from] = 0;
    }
 
 
    //get augmented path
    auto buildAug = [&]() {
 
        edge fake = {0, -1, 0, -1, 10000000000};
 
        deque<edge> dfs; dfs.push_back(fake); //using deque as stack
        set<int> visited = {0};
    
        while (dfs.size() > 0 && dfs.back().snk != n - 1 && visited.size() != n) {
            bool nxt = false;
            int src = dfs.back().snk;
 
            for (int i = 0; i < c[src].size() ; i++) {
                edge e = c[src][i];
                if (e.spd > 0 && !visited.count(e.snk)) {
                    visited.insert(e.snk);
                    dfs.push_back(e);
                    nxt = true;
                    break;
                }
            }
 
            if (nxt) continue;
 
            for (int i = 0; i < cRev[src].size(); i++) {
                edge r = cRev[src][i];
                if (r.spd > 0 && !visited.count(r.snk)) {
                    visited.insert(r.snk);
                    dfs.push_back(r);
                    nxt = true;
                    break;
                }
            }
 
            if (nxt) continue;
 
            dfs.pop_back(); //removes nodes in path that have no path forward
        }
 
        vector<edge> path;
 
        while (dfs.size() > 1) {
            dfs.pop_front(); //pop fake edge or previously added edges
 
            path.push_back(dfs.front());
        }
 
        return path;
 
    };
 
    ll maxFlow = 0;
    vector<edge> aug = buildAug();  
    //if path size is 0, does not exist  
    while (aug.size() > 0 && aug.back().snk == n - 1) {
 
        ll choke = 1e10;
        for (int i = 0; i < aug.size(); i++) {
            choke = min(choke, aug[i].spd);
        }
 
        for (edge e : aug) {
            // c[e.from][e.fdx].spd -= choke;
            //from i to j
            graph[i][j] -= choke;
            graph[j][i] += choke;
            // cRev[e.snk][e.rdx].spd += choke;
        }
 
        maxFlow += choke;
 
        aug = buildAug();
    }
 
    cout << maxFlow << endl;
 
    return 0;
}