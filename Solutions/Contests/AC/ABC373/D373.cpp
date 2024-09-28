#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    vector<vector<array<ll,2> > > adj(n);

    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back(array<ll,2>{v,w});
        adj[v].push_back(array<ll,2>{u,-w});
    }

    vector<ll> res(n,-1);
    for(int i = 0; i < n; i++) {
        if(res[i] == -1) {

            queue<array<ll,2> > q;
            q.push({i,0});
            while(q.size()) {
                auto [idx, w] = q.front();
                q.pop();

                if(res[idx] != -1) continue;

                res[idx] = w;
                for(auto [v, c] : adj[idx]) {
                    q.push({v, w + c});
                }

            }

        }
    }

    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }

    return 0;
}
