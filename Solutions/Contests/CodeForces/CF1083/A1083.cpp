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

ll solve_fast(int n, vector<ll> a, vector<vector<array<ll,2>>> adj) {

    vector<ll> dp(n);
    ll ans = 0;

    auto dfs0 = [&](auto self, int i, int p) -> void {
        ll res = a[i];
        for(auto [c, d] : adj[i]) {
            if(c != p) {
                self(self, c, i);
                res = max(res, a[i] + dp[c] - d);
            }
        }
        dp[i] = res;
        ans = max(ans, dp[i]);
    };

    

    auto dfs1 = [&](auto self, int i, int p) -> void {
        vector<array<ll,2>> ch;
        for(auto [c, d] : adj[i]) {
            ans = max(ans, a[i] + dp[c] - d);
            ch.push_back({a[i] + dp[c] - d, c});
        }
        // cout << "i : " << i << " ch : " << ch << endl;
        sort(ch.begin(), ch.end());
        for(auto [c, d] : adj[i]) {
            if(c != p) {
                dp[i] = 0;
                for(int j = sz(ch) - 1; j >= 0; j--) {
                    if(ch[j][1] != c) {
                        dp[i] = ch[j][0];
                        break;
                    }
                }
                self(self, c, i);
            }
        }
    };

    dfs0(dfs0, 0, -1);
    // cout << "dp : " << dp << endl;
    dfs1(dfs1, 0, -1);

    // cout << ans << '\n';

    return ans;

}

ll solve_slow(int n, vector<ll> a, vector<vector<array<ll,2>>> adj) {
    ll res = 0;
    auto dfs = [&](auto self, int i, int p, ll gas) -> void {
        if(gas < 0) return;
        gas += a[i];
        res = max(res, gas);
        for(auto [c, d] : adj[i]) {
            if(c != p) {
                self(self, c, i, gas - d);
            }
        }
    };

    for(int i = 0; i < n; i++) {
        dfs(dfs, i, -1, 0);
    }
    return res;
}

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
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
    dsu[y] = x;
    sizes[x] += sizes[y];
}

const int debug = 0;
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(debug == 0) {
        int n; cin >> n;
        vector<ll> a(n);
        for(ll &x : a) cin >> x;

        vector<vector<array<ll,2>>> adj(n);
        for(int i = 1; i < n; i++) {
            int u, v, w; cin >> u >> v >> w;
            u--; v--;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        cout << solve_fast(n, a, adj) << '\n';
    } else {
        for(int tc = 0; tc < 1000; tc++) {
            int n = rng() % 5 + 1;
            vector<ll> a(n);
            for(int i = 0; i < n; i++) a[i] = rng() % 10;
            dsubuild(n);
            vector<vector<array<ll,2>>> adj(n);
            for(int i = 1; i < n; i++) {
                int u = rng() % n, v = rng() % n;
                while(find(u) == find(v)) {
                    v = rng() % n;
                }
                ll w = rng() % 10;
                // cout << "u : " << u << " v : " << v << endl;
                adj[u].push_back({v, w});
                adj[v].push_back({u, w});
                merge(u, v);
            }

            ll res_slow = solve_slow(n, a, adj);
            ll res_fast = solve_fast(n, a, adj);
            if(res_slow != res_fast) {
                cout << "slow (c) : " << res_slow << endl;
                cout << "fast (wa) : " << res_fast << endl;
                cout << n << endl;
                cout << a << endl;
                for(int i = 0; i < n; i++) {
                    cout << "i : " << i << " adj[i] : " << adj[i] << endl;
                }
                assert(0);
            }
        }
        cout << "ALL TESTS PASSING" << endl;
    }


    return 0;
}
