#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[y] = x;
        sizes[x] += sizes[y];
    }
}

int dp[400][400][400];
int a0[400], ta0[400];

void solve() {
    int n, m, q; cin >> n >> m >> q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                dp[i][j][k] = 1e9;
            }
        }
    }
    vector<array<int,3>> edges;
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges.push_back({u-1,v-1,w});
    }
    sort(edges.begin(), edges.end(), [](const auto &lhs, const auto &rhs) -> bool {
        return lhs[2] < rhs[2];
    });

    dsubuild(n);
    vector<int> in_mst(m);
    vector<vector<int>> adj0(n), adj1(n);

    for(int i = 0; i < m; i++) {
        if(find(edges[i][0]) != find(edges[i][1])) {
            in_mst[i] = 1;
            merge(edges[i][0], edges[i][1]);
        }
        adj1[edges[i][0]].push_back(edges[i][1]);
        adj1[edges[i][1]].push_back(edges[i][0]);
    }

    auto get_dist = [&](int s, vector<int> &dists)  {
        // queue<array<int,2>> q;
        // q.push({s, 0});
        // dists[s] = 0;
        // while(q.size()) {
        //     auto [si, sd] = q.front();
        //     q.pop();
        //     queue<array<int,2>> q0;
        //     vector<int> t;
        //     q0.push({si, sd});
        //     while(q0.size()) {
        //         auto [i, d] = q0.front();
        //         q0.pop();
        //         t.push_back(i);
        //         for(int x : adj0[i]) {
        //             if(dists[x] == -1) {
        //                 q0.push({x,d});
        //                 dists[x] = d;
        //             }
        //         }
        //         for(int x : adj1[i]) {
        //             if(dists[x] == -1) {
        //                 q.push({x, d + 1});
        //                 dists[x] = d + 1;
        //             }
        //         }
        //     }
        // }
        int pa0 = -1, pta0 = -1, l = 0;
        a0[0] = s;
        dists[s] = 0;
        pa0 = 0;
        while(pa0 != -1) {
            while(pa0 != -1) {
                int x = a0[pa0--];
                ta0[++pta0] = x;
                for(int c : adj0[x]) {
                    if(dists[c] == -1) {
                        dists[c] = l;
                        a0[++pa0] = c;
                    }
                }
            }
            while(pta0 != -1) {
                int x = ta0[pta0--];
                for(int c : adj1[x]) {
                    if(dists[c] == -1) {
                        dists[c] = l + 1;
                        a0[++pa0] = c;
                    }
                }
            }
            l++;
        }
    };

    for(int i = 0; i < m; i++) {
        if(in_mst[i]) {
            vector<int> a(n,-1), b(n,-1);
            get_dist(edges[i][0], a);
            get_dist(edges[i][1], b);

            // cout << "in mist edge : " << edges[i] << '\n';
            // cout << "a : " << a << '\n';
            // cout << "b : " << b << '\n';

            for(int j = 0; j < n; j++) {
                for(int k = 0; k <= j; k++) {
                    int md = min(a[j] + b[k], a[k] + b[j]);
                    if(md < n) {
                        dp[j][k][md] = min(dp[j][k][md], edges[i][2]);
                        dp[k][j][md] = min(dp[k][j][md], edges[i][2]);
                    }
                }
            }

            adj0[edges[i][0]].push_back(edges[i][1]);
            adj0[edges[i][1]].push_back(edges[i][0]);
        }
    }

    for(int i = 0; i < q; i++) {
        int a, b, k; cin >> a >> b >> k;
        cout << dp[a-1][b-1][k-1] << " \n"[i == q - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}