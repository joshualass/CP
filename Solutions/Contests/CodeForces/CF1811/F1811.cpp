#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
conditions for flower
In order to be an n-flower, need exactly n^2 nodes.
n of these nodes will have degree 4. The other n * (n - 1) nodes have degree 2. 
A cycle of the length n from the n flower nodes. 
Each flower node have a cycle of length n.

*/

void solve() {
    
    int n, m; cin >> n >> m;

    int k = 1;
    while(k * k < n) {
        k++;
    }

    int ok = 1;

    if(k * k != n) {
        ok = 0;
    }

    vector<int> flowernodes;
    vector<int> isflower(n);

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        if(adj[u].size() == 4) {
            flowernodes.push_back(u);
            isflower[u] = 1;
        }
        if(adj[v].size() == 4) {
            flowernodes.push_back(v);
            isflower[v] = 1;
        }
    }

    int nearflower = 0, nearpetal = 0;

    for(int i = 0; i < n; i++) {
        if(isflower[i]) {
            int petalnei = 0, flowernei = 0;
            for(int c : adj[i]) {
                if(isflower[c]) {
                    flowernei++;
                } else {
                    petalnei++;
                }
            }
            if(flowernei != 2 || petalnei != 2) {
                ok = 0;
            }
        }
        if(!isflower[i]) {
            int fc = 0, pc = 0;
            for(int c : adj[i]) {
                if(isflower[c]) {
                    fc++;
                } else {
                    pc++;
                }
            }
            if(fc == 1 && pc == 1) {
                nearflower++;
            } else if(fc == 0 && pc == 2) {
                nearpetal++;
            } else {
                ok = 0;
            }
        }
    }

    if(flowernodes.size() != k || nearflower != k * 2 || nearpetal != k * (k - 3)) {
        ok = 0;
    }

    vector<int> vis(n);

    auto dfsflower = [&](auto self, int i) -> void {

        if(vis[i]) return;
        vis[i] = 1;
        for(int c : adj[i]) {
            if(isflower[c]) {
                self(self,c);
            }
        }

    };

    if(flowernodes.size()) {
        dfsflower(dfsflower,flowernodes[0]);
    } else {
        ok = 0;
    }

    if(reduce(vis.begin(), vis.end()) != k) {
        ok = 0;
    }

    auto vispetal = [&](auto self, int i, int &viscount) -> void {
        if(vis[i]) return;
        vis[i] = 1;
        viscount++;

        for(int c : adj[i]) {
            if(!isflower[c]) {
                self(self, c, viscount);
            }
        }

    };

    for(int flower : flowernodes) {

        int cnt = 0;
        vis[flower] = 0;
        vispetal(vispetal, flower, cnt);
        if(cnt != k) {
            ok = 0;
        }

    }

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}