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

    vector<vector<ll>> dist(n, vector<ll>(n, 1e10));
    ll apsp = 0;

    auto g = [&](int i, int j) -> ll {
        if(i > j) swap(i, j);
        return dist[i][j];
    };

    auto u = [&](int i, int j, ll d) -> void {
        if(i > j) swap(i, j);
        if(d < dist[i][j]) {
            if(dist[i][j] != 1e10) apsp -= dist[i][j];
            dist[i][j] = d;
            apsp += d;
        }
    };

    for(int i = 0; i < n; i++) {
        u(i, i, 0);
    }

    for(int i = 0; i < m; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        u(a, b, c);
    }

    ll k, t; cin >> k >> t;
    vector<int> d;
    for(int i = 0; i < k; i++) {
        int di; cin >> di;
        di--;
        for(int x : d) {
            u(di, x, t);
        }
        d.push_back(di);
    }

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                u(i, j, g(i, k) + g(k, j));
            }
        }
    }

    vector<ll> ad(n, 1e10);

    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int qt; cin >> qt;
        if(qt == 1) {
            int x, y, t; cin >> x >> y >> t;
            x--; y--;
            ud(x, y, t);
            ud(y, x, t);
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    ud(i, j, dist[i][x] + dist[x][y] + dist[y][j]);
                    ud(i, j, dist[i][y] + dist[y][x] + dist[x][j]);
                }
            }
        } else if(qt == 2) {
            int x; cin >> x;
            x--;
            for(int i = 0; i < n; i++) {
                for(int x : d) {
                    ad[i] = min(ad[i], dist[i][x]);
                }
            }
            // cout << "ad : " << ad << '\n';
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    ud(i, j, dist[i][x] + t + ad[j]);
                    ud(i, j, ad[i] + t + dist[j][x]);
                }
            }
            d.push_back(x);
        } else {
            cout << apsp << '\n';
        }
        // cout << "qq : " << qq << " apsp\n";
        // for(int i = 0; i < n; i++) cout << dist[i] << '\n';
    }

    return 0;
}
