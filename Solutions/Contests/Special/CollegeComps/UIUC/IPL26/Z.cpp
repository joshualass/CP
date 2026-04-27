#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

const ll inf = 1e18;

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

    ll n, m; cin >> n >> m;
    vector<ll> t(n);
    for(ll &x : t) cin >> x;

    vector<vector<ll>> a(n);
    for(ll i = 0; i < m; i++) {
        ll s, u; cin >> s >> u;
        s--;
        a[s].push_back(u);
    }

    vector<vector<array<ll,2>>> qt(n); // {time, wait time for joining at time time}
    
    for(ll i = 0; i < n; i++) {
        sort(a[i].begin(), a[i].end());
        qt[i].push_back({0, 0});
        for(ll vis : a[i]) {
            if(qt[i].back()[0] == vis) {
                qt[i].back()[1] += t[i];
            } else {
                qt[i].push_back({vis, max(t[i], t[i] + qt[i].back()[1] - (vis - qt[i].back()[0]))});
            }
        }
        // cout << "i : " << i << " qt[i] : " << qt[i] << endl;
    }

    auto wt = [&](ll shop, ll vis_time) -> ll {
        auto [time, wt] = *--(upper_bound(qt[shop].begin(), qt[shop].end(), array<ll,2>{vis_time, inf}));
        ll res = max(0LL, wt - (vis_time - time)) + t[shop];
        // cout << "shop : " << shop << " vis_time : " << vis_time << " res : " << res << endl;
        return res;
    };

    vector<ll> dp(1 << n, inf);
    dp[0] = 0;

    for(int bm = 1; bm < 1 << n; bm++) {
        for(int prev = 0; prev < n; prev++) {
            if((bm >> prev) & 1) {
                int pbm = bm ^ (1 << prev);
                ll vis_time = dp[pbm];
                // cout << "bm : " << bm << " prev : " << prev << " vt : " << vis_time << endl;
                dp[bm] = min(dp[bm], vis_time + wt(prev, vis_time));
            }
        }
        // cout << "bm : " << bm << " dp : " << dp[bm] << endl;
    }

    cout << dp[(1 << n) - 1] << '\n';

    return 0;
}
