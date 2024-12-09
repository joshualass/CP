#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    vector<vector<int>> mat(n,vector<int>(m));
    for(auto &x : mat) for(auto &y : x) {
        cin >> y;
        y--;
    }

    vector<vector<int>> supports(9902);
    vector<vector<int>> supportedby(9902);

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < m; j++) {
            supports[mat[i][j]].push_back(mat[i-1][j]);
            supportedby[mat[i-1][j]].push_back(mat[i][j]);
        }
    }

    queue<array<int,2>> q;

    auto bfs = [&](vector<vector<int>> &adj, vector<int> &dists) -> void {
        // cout << "dists size : " << dists.size() << '\n';
        while(q.size()) {
            auto [block,cnt] = q.front();
            q.pop();
            // cout << "block : " << block << endl;
            if(dists[block] != -1) continue;
            dists[block] = cnt;
            for(int x : adj[block]) {
                q.push({x,cnt+1});
            }
        }

    };

    for(int i = 0; i < m; i++) {
        q.push({mat[n-1][i],1});
    }

    vector<int> dist_bottoms(9902,-1);
    bfs(supports,dist_bottoms);

    vector<vector<int>> top_supports;
    set<int> top_vis;

    for(int i = 0; i < m; i++) {
        if(top_vis.count(mat[0][i]) == 0) {
            top_vis.insert(mat[0][i]);
            top_supports.push_back(vector<int>(9902,-1));
            q.push({mat[0][i],1});
            bfs(supportedby,top_supports[top_supports.size() - 1]);
        }
    }

    if(top_supports.size() == 1) {
        cout << dist_bottoms[*top_vis.begin()] << '\n';
    } else {
        // cout << "no\n";

        int comp1 = *top_vis.begin();
        int comp2 = *++top_vis.begin();

        int res = dist_bottoms[comp1] + dist_bottoms[comp2];

        for(int i = 0; i < 9902; i++) {
            if(dist_bottoms[i] != -1 && top_supports[0][i] != -1 && top_supports[1][i] != -1) {
                res = min(res, dist_bottoms[i] + top_supports[0][i] + top_supports[1][i] - 2);
            }
        }
        cout << res << '\n';
    }

    return 0;
}