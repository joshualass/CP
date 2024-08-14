#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
broken by
7
1 2
2 3
3 4
4 5
4 6
5 7

solution: prioritize leaves

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<set<array<int,2>>> children(n);
    vector<int> par(n);
    vector<int> vis(n,0);
    vis[0] = -1;

    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> res;
    bool ok = 1;

    auto insigination = [&](auto self, int i, int p) -> void {

        par[i] = p;

        for(int c : adj[i]) {
            if(c != p) {
                int notleaf = adj[c].size() != 1;
                children[i].insert({notleaf,c});
                self(self, c, i);
            }
        }

    };

    insigination(insigination, 0, -1);

    auto dfs = [&](auto self, int i) -> void {
        int p = par[i];
        res.push_back(i);
        vis[i]++;
        if(i) {
            int notleaf = adj[i].size() != 1;
            children[par[i]].erase({notleaf,i});
        } else if(vis[i]) {
            return;
        }


        for(int c : adj[i]) {
            if(c != p && children[c].size()) {
                self(self, (*children[c].begin())[1]);
                return;
            }
        }

        for(int c : adj[i]) {
            if(c != p && !vis[c]) {
                self(self,c);
                return;
            }
        }

        if(i) {
            if(children[par[i]].size()) {
                self(self, (*children[par[i]].begin())[1]);
                return;
            }
        }

        if(i) {
            if(!vis[par[i]]) {
                self(self, par[i]);
            } else if(par[i] && !vis[par[par[i]]]) {
                self(self, par[par[i]]);
            }
        }

    };

    dfs(dfs,0);

    // cout << "res : " << res << '\n';

    if(res.size() == n + 1) {
        cout << "Yes\n";
        for(int i = 0; i < n; i++) {
            cout << res[i] + 1 << " \n"[i == n - 1];
        }
    } else {
        cout << "No\n";
    }

    return 0;
}