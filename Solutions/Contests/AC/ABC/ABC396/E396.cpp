#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<array<int,2>>> adj(n);
    for(int i = 0; i < m; i++) {
        int x, y, z; cin >> x >> y >> z;
        x--; y--;
        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
    }    

    vector<int> vis(n, -1);
    int ok = 1;

    auto dfs = [&](auto self, int i, int req, int &size, vector<int> &cnts) -> void {

        if(vis[i] == -1) {
            vis[i] = req;
            for(int j = 0; j < 30; j++) cnts[j] += (req >> j) & 1;
            size++;
            for(auto [to, z] : adj[i]) self(self, to, z ^ req, size, cnts);
        } else if(req != vis[i]) ok = 0;

    };

    vector<int> reqs(n, -1);

    for(int i = 0; i < n; i++) {
        if(vis[i] == -1) {
            vector<int> cnts(30);
            int size = 0;
            dfs(dfs, i, 0, size, cnts);
            int res = 0;
            for(int j = 0; j < 30; j++) {
                if(cnts[j] > size - cnts[j]) {
                    res += 1 << j;
                }
            }
            reqs[i] = res;
        }
    }

    vis.assign(n, -1);
    int sz = 0;
    vector<int> temp(30);
    for(int i = 0; i < n; i++) if(reqs[i] != -1) dfs(dfs, i, reqs[i], sz, temp);

    if(ok) {
        for(int x : vis) cout << x << ' ';
        cout << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}