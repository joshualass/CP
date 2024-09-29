#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = -1;
    for(int i = 0; i < n; i++) {
        if(adj[i].size() != 1) {
            root = i;
        }
    }

    //find # of leaves in each subtree
    vector<int> numleaves(n);
    auto dfs = [&](auto self, int i, int p) -> void {
        numleaves[i] = adj[i].size() == 1;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                numleaves[i] += numleaves[c];
            }
        }
    };

    dfs(dfs, root, -1);

    auto comp = [](const vector<int> &lhs, const vector<int> &rhs) -> bool {
        return lhs.size() > rhs.size();
    };


    priority_queue<array<int,2>> pq;
    vector<vector<int>> vectors;

    auto dfs2 = [&](auto self, int i, int p, vector<int> &v, int gimmejimmy) -> void {
        
        //we are collecting goons and putting them to vector bc we can
        if(gimmejimmy) {
            if(adj[i].size() == 1) {
                v.push_back(i);
            }
            for(int c : adj[i]) {
                if(c != p) {
                    self(self, c, i, v, gimmejimmy);
                }
            }
            return;
        }
        //if we have one leaf in the subtree, gimmejimmy should be active. 
        int maxc = -1;
        for(int c : adj[i]) {
            if(c != p && (maxc == -1 || numleaves[c] > numleaves[maxc])) {
                maxc = c;
            }
        }

        int maxsize = numleaves[maxc];
        if(maxsize > n / 2) {
            for(int c : adj[i]) {
                if(c != p && c != maxc) {
                    self(self, c, i, v, 1);
                    pq.push({v.size(), vectors.size()});
                    vectors.push_back(v);
                    v.clear();
                }
            }
            self(self, maxc, i, v, 0);
        } else {
            for(int c : adj[i]) {
                if(c != p) {
                    self(self, c, i, v, 1);
                    pq.push({v.size(), vectors.size()});
                    vectors.push_back(v);
                    v.clear();
                }
            }
        }

    };

    vector<array<int,2>> res;
    while(pq.size() >= 2) {
        auto [s1, v1] = pq.top();
        pq.pop();
        auto [s2, v2] = pq.top();
        pq.pop();

        res.push_back({vectors[v1].back(), vectors[v2].back()});
        vectors[v1].pop_back();
        vectors[v2].pop_back();

    }

    return 0;
}