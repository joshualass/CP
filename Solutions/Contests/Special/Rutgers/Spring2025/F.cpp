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
    
    int n, m; cin >> n >> m;
    vector<vector<array<int,2>>> adj(n);

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        char c; cin >> c;
        int t = c == 'R';
        adj[u].push_back({v, t});
        adj[v].push_back({u, t});
    }

    int ok = 1;
    vector<array<int,2>> d(n, array<int,2>{-1,-1});

    auto dfs = [&](auto self, int i, int c) -> int {
        if(d[i][c] == -2) {
            ok = 0;
            return 0;
        }
        if(d[i][c] != -1) {
            return d[i][c];
        }
        d[i][c] = -2;

        // cout << "start i : " << i << " c : " << c << '\n';

        int b = 0;
        for(auto [to, uc] : adj[i]) {
            if(c + uc == 1) {
                b = max(b, 1 + self(self, to, uc));
            }
        }
        // cout << "end i : " << i << " c : " << c << " b : " << b << '\n';

        d[i][c] = b;
        return d[i][c];
    };

    array<int,2> res = {};

    for(int i = 0; i < n; i++) {
        for(int c = 0; c < 2; c++) {
            if(d[i][c] == -1) dfs(dfs, i, c);
        }
        int sr = d[i][0], sb = d[i][1];

        if((sr + sb) & 1) {
            if(sr & 1) {
                res[0] = max(res[0], sr + sb + 1);
                res[1] = max(res[1], sr + sb);
            } else {
                res[0] = max(res[0], sr + sb);
                res[1] = max(res[1], sr + sb + 1);
            }
        } else {
            res[0] = max(res[0], sr + sb + 1);
            res[1] = max(res[1], sr + sb + 1);
        }

    }

    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " d[i] : " << d[i] << '\n';
    // }

    // cout << "res : " << res << '\n';

    if(ok) {
        string s = "";
        if(res[0] < res[1]) {
            for(int i = 0; i < res[0]; i++) {
                s.push_back((i & 1 ? 'B' : 'R'));
            }
        } else {
            for(int i = 0; i < res[1]; i++) {
                s.push_back((i & 1 ? 'R' : 'B'));
            }
        }
        cout << s << '\n';
    } else {
        cout << "-1\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}