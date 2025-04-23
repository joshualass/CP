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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

void solve() {

    int n; cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n));
    for(auto &x : a) for(auto &y : x) cin >> y;

    auto solve0 = [](vector<vector<ll>> a, vector<ll> h, int n) -> ll {
        vector<array<ll,2>> dp(n, {-1,-1});
        dp[0][0] = 0;
        dp[0][1] = h[0];

        for(int i = 1; i < n; i++) {
            set<int> bad;
            for(int j = 0; j < n; j++) {
                bad.insert(a[i][j] - a[i-1][j]);
            }
            // cout << "i : " << i << " bad : " << bad << '\n';
            for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 2; k++) {
                    if(dp[i-1][k] != -1) {
                        if(bad.count(k - j) == 0) {
                            if(dp[i][j] == -1 || dp[i-1][k] < dp[i][j]) dp[i][j] = dp[i-1][k];
                        }
                    }
                }
                if(dp[i][j] != -1 && j) dp[i][j] += h[i];
            }
        }

        // cout << "dp : " << dp << '\n';

        array<ll,2> res = dp.back();
        if(res[0] == -1 || res[1] == -1) {
            if(res[0] != -1) return res[0];
            if(res[1] != -1) return res[1];
            return -1;
        } else {
            return min(res[0], res[1]);
        }
    };

    ll res = 0;
    vector<ll> h(n);
    for(ll &x : h) cin >> x;
    res = solve0(a, h, n);

    for(ll &x : h) cin >> x;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            swap(a[i][j], a[j][i]);
        }
    }

    ll t0 = solve0(a, h, n);
    if(t0 != -1 && res != -1) res += t0;
    else res = -1;

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}