#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);

    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<array<int,3>>> cc(n); // {centroid, index of child it is a child of, distance}
    vector<int> vis(n), ss(n);
    vector<multiset<int>> dis(n);
    vector<vector<multiset<int>>> best(n);
    vector<int> color(n);
    multiset<int> ms;
    
    auto dfs = [&](auto self, int start) -> void {
        if(vis[start]) return;
        // cout << "start : " << start << endl;
        auto dfs0 = [&](auto self, int i, int p) -> void {
            if(vis[i]) return;
            int res = 1;
            for(int c : adj[i]) {
                if(c != p) {
                    self(self, c, i);
                    res += ss[c];
                }
            }
            ss[i] = res;
        };

        dfs0(dfs0, start, -1);

        // cout << "0 ok ss : " << ss << endl;


        int centroid = -1;
        int total_size = ss[start];

        auto dfs1 = [&](auto self, int i, int p) -> void {
            if(vis[i]) return;
            int ok = 1;
            // cout << "dfs1 i : " << i << endl;
            for(int c : adj[i]) {
                // cout << "c : " << c << " ss[c] : " << ss[c] << endl;
                if(ss[c] * 2 > total_size) ok = 0;
            }
            if(ok) centroid = i;
            for(int c : adj[i]) {
                if(c != p) {
                    ss[i] = total_size - ss[c];
                    self(self, c, i);
                }
            }
        };

        dfs1(dfs1, start, -1);

        // cout << "1 ok centroid : " << centroid << endl;

        assert(centroid != -1);
        vis[centroid] = 1;
        ss[centroid] = 0;

        auto dfs2 = [&](auto self, int i, int p, int d) -> void {
            if(vis[i]) return;
            int idx = sz(best[centroid]) - 1;
            cc[i].push_back({centroid, idx, d});
            for(int c : adj[i]) {
                if(c != p) {
                    self(self, c, i, d + 1);
                }
            }
        };

        cc[centroid].push_back({centroid, 0, 0});
        best[centroid].push_back({});

        for(int c : adj[centroid]) {
            best[centroid].push_back({});
            dfs2(dfs2, c, centroid, 1);
        }

        // cout << "dfs2 done" << endl;

        for(int c : adj[centroid]) {
            self(self, c);
        }
    };

    dfs(dfs, 0);

    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " cc[i] : " << cc[i] << endl;
    // }

    auto toggle = [&](int i) -> void {
        for(auto [centroid, ci, d] : cc[i]) {
            if(sz(dis[centroid]) >= 2) {
                auto it = dis[centroid].end();
                int first = *--it;
                int second = *--it;
                ms.erase(ms.find(first + second));
            }

            if(!best[centroid][ci].empty()) {
                auto it = best[centroid][ci].end();
                int val = *--it;
                dis[centroid].erase(dis[centroid].find(val));
            }

            if(color[i] == 0) {
                best[centroid][ci].insert(d);
            } else {
                best[centroid][ci].erase(best[centroid][ci].find(d));
            }

            if(!best[centroid][ci].empty()) {
                auto it = best[centroid][ci].end();
                int val = *--it;
                dis[centroid].insert(val);
            }

            if(sz(dis[centroid]) >= 2) {
                auto it = dis[centroid].end();
                int first = *--it;
                int second = *--it;
                ms.insert(first + second);
            }
        }
        color[i] ^= 1;
    };

    for(int i = 0; i < n; i++) toggle(i);

    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int x; cin >> x;
        x--;
        toggle(x);
        assert(!ms.empty());
        int val = *--ms.end();
        cout << val << '\n';
    }

    return 0;
}
