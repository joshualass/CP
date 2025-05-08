#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> a(n,1), dep(n), par(n);
    vector<array<int,3>> ops;

    auto dfs0 = [&](auto self, int i, int p, int d) -> void {
        dep[i] = d;
        par[i] = p;
        for(int c : adj[i]) {
            if(c != p) self(self, c, i, d + 1);
        }
    };

    dfs0(dfs0, 0, -1, 0);

    auto dfs = [&](auto self, int rt) -> void {
        array<int,3> b = {};

        auto dfs1 = [&](auto self, int i, int p) -> array<int,2> {
            priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq;
            pq.push({0, i});
            pq.push({0, i});

            for(int c : adj[i]) {
                if(c != p && a[c]) {
                    array<int,2> t = self(self, c, i);
                    if(t > pq.top()) {
                        pq.pop();
                        pq.push(t);
                    }
                }
            }
            assert(pq.size() == 2);
            array<int,2> s = pq.top();
            pq.pop();
            array<int,2> f = pq.top();
            array<int,3> o = {1 + f[0] + s[0], max(f[1], s[1]), min(f[1],s[1])};
            b = max(b, o);
            f[0]++;
            return f;
        };

        dfs1(dfs1, rt, -1);

        ops.push_back(b);
        int u = b[1], v = b[2];

        vector<int> in_path;
        while(u != v) {
            if(dep[u] > dep[v]) {
                a[u] = 0;
                in_path.push_back(u);
                u = par[u];
            } else {
                a[v] = 0;
                in_path.push_back(v);
                v = par[v];
            }
        }
        a[u] = 0;
        in_path.push_back(u);

        for(int p : in_path) for(int nei : adj[p]) if(a[nei]) self(self, nei);

    };

    dfs(dfs, 0);
    sort(ops.rbegin(), ops.rend());

    for(auto op : ops) cout << op[0] << " " << op[1] + 1 << " " << op[2] + 1 << " ";
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// void solve() {
    
//     int n; cin >> n;
//     vector<vector<int>> adj(n);
//     for(int i = 1; i < n; i++) {
//         int u, v; cin >> u >> v;
//         u--; v--;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }

//     vector<array<int,2>> d(n);
//     vector<int> par(n), dep(n);

//     auto dfs = [&](auto self, int i, int p, int cd) -> void {
//         array<int,2> a = {0, i};
//         for(int c : adj[i]) {
//             if(c != p) {
//                 self(self, c, i, cd + 1);
//                 if(d[c] > a) a = d[c];
//             }
//         }
//         a[0]++;
//         d[i] = a;
//         par[i] = p;
//         dep[i] = cd;
//     };

//     dfs(dfs, 0, -1, 0);
//     vector<map<int, array<int,3>>> m(n);
//     array<int,3> st = {};

//     auto dfs1 = [&](auto self, int i, int p) -> void {
//         vector<array<int,3>> ch; //{d, path, neighbor}
//         ch.push_back({0, i, i});
//         ch.push_back({0, i, i});

//         for(int c : adj[i]) {
//             ch.push_back({d[c][0], d[c][1], c});
//         }

//         sort(ch.rbegin(), ch.rend());
//         array<int,3> t = {ch[0][0] + 1, ch[0][1], i};
//         if(ch[0][1] < i) swap(t[1], t[2]);
//         st = max(st, t);

//         for(int c : adj[i]) {
//             vector<array<int,3>> b;
//             for(int i = 0; i < ch.size(); i++) {
//                 if(ch[i][2] != c) {
//                     b.push_back(ch[i]);
//                     if(b.size() == 2) break;
//                 }
//             }

//             auto f = b[0], s = b[1];

//             m[i][c] = {1 + f[0] + s[0], max(f[1], s[1]),min(f[1], s[1])};
//             if(c != p) {
//                 d[i] = {f[0] + 1, f[1]};
//                 self(self, c, i);
//             }
//         }
//     };

//     dfs1(dfs1, 0, -1);

//     vector<array<int,3>> ops;
//     queue<array<int,3>> q;
//     q.push(st);
//     vector<int> has_apple(n, 1);
//     while(q.size()) {
//         auto [d, u, v] = q.front();
//         ops.push_back(q.front());
//         if(ops.back()[1] < ops.back()[2]) swap(ops.back()[1], ops.back()[2]);
//         q.pop();
//         vector<int> rem;
//         while(u != v) {
//             if(dep[u] > dep[v]) {
//                 has_apple[u] = 0;
//                 rem.push_back(u);
//                 u = par[u];
//             } else {
//                 has_apple[v] = 0;
//                 rem.push_back(v);
//                 v = par[v];
//             }
//         }

//         has_apple[u] = 0;
//         rem.push_back(u);

//         for(int x : rem) for(int y : adj[x]) if(has_apple[y]) q.push(m[y][x]);

//     }

//     sort(ops.rbegin(), ops.rend());
//     for(auto op : ops) {
//         cout << op[0] << " " << op[1] + 1 << " " << op[2] + 1 << " ";
//     }
//     cout << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }