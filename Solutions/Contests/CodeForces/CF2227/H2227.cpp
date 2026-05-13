#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

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

    auto dfs = [&](auto self, int i, int p) -> array<int,3> {

        array<int,3> res;

        if(sz(adj[i]) == 1) {
            res = {1, 1, 0};
        } else {
            int cur = 0;
            vector<array<int,3>> ch;
            int par = 0;
            for(int c : adj[i]) {
                if(c != p) {
                    array<int,3> nx = self(self, c, i);
                    par ^= nx[0];
                    cur += nx[1];
                    ch.push_back(nx);
                }
            }

            res = {par, cur, cur};
            for(auto c : ch) {
                res[2] = min(res[2], cur - c[1] + c[2]);
            }

            if(par == 0) {
                res[2]++;
            } else {
                res[1]++;
            }
        }
        // cout << "i : " << i << " p : " << p << " dp : " << res << endl;
        return res;
    };

    array<int,3> res;
    for(int i = 0; i < n; i++) {
        if(sz(adj[i]) > 1) {
            res = dfs(dfs, i, -1);
            break;
        }
    }

    int ans = res[1];
    if(res[0] == 1) {
        ans = min(ans, res[2]);
    }

    cout << ans << '\n';

    // int ans = 0;

    // auto dfs = [&](auto self, int i, int p) -> vector<int> {
    //     vector<vector<int>> ch;
    //     for(int c : adj[i]) {
    //         if(c != p) {
    //             auto r = self(self, c, i);
    //             if(sz(r)) ch.push_back(r);
    //         }
    //     }

    //     if(sz(ch) % 2 == 0) {
    //         vector<int> res = {inf, inf};

    //         int s = 0;
    //         for(auto c : ch) {
    //             s += c[0];
    //         }

    //         res[0] = s + 1;
    //         res[1] = s;

    //         for(auto c : ch) {
    //             res[1] = min(res[1], s - c[0] + c[1]);
    //         }

    //         return res;
    //     } else {
    //         for(auto c : ch) {
    //             ans += c[0];
    //         }
    //         return {};
    //     }

    // };

    // auto res = dfs(dfs, 0, -1);
    // if(sz(res)) {
    //     ans += res[1];
    // }

    // cout << ans << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}