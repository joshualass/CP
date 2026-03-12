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
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

const int MAXLEN = 100000;
const int MOD = 998244353;
template <int len = 1>
int solve(int n, int x, int y, string &s) {
    if(n >= len) {
        return solve<min(len * 2, MAXLEN + 1)>(n, x, y, s);
    }
    bitset<len> dp0 {};
    bitset<len> dp1 {};

    dp0[0] = 1;
    for(char c : s) {
        if(c == '0') {
            dp1 <<= 1;
        } else if(c == '1') {
            swap(dp0, dp1);
            dp1 <<= 1;
        } else {
            dp0 |= dp1;
            dp1 |= dp0;
            dp1 <<= 1;
        }
    }

    auto tri = [&](ll x) -> ll {
        return x * (x + 1) / 2;
    };

    set<ll> vis;
    for(int i = 0; i <= n; i++) {
        ll t;
        if(i <= n / 2) {
            t = n - i * 2;
        } else {
            t = i * 2 - n - 1;
        }
        ll xc = tri(t);
        // cout << "n : " << n << " y : " << i << " xc : " << xc << endl;
        if(dp0[i] || dp1[i]) vis.insert(x * xc + 1LL * i * y);
    }

    // cout << "vis : " << vis << endl;

    ll res = 0;
    for(ll x : vis) res += x % MOD;
    return res % MOD;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int len = 10;
    // vector<set<array<int,2>>> a(len + 1);


    // auto dfs = [&](auto self, int cx, int cy, int sx, int sy, int idx) -> void {
    //     a[idx].insert({sx, sy});
    //     if(idx < len) {
    //         self(self, cx + 1, cy, sx + (cx + 1), sy + cy, idx + 1);
    //         self(self, -cx, 1 - cy, sx - cx, sy + (1 - cy), idx + 1);
    //     }
    // };

    // dfs(dfs, 0, 0, 0, 0, 0);

    // for(int i = 1; i <= len; i++) cout << "i : " << i << " map : " << a[i] << endl;

    int casi; cin >> casi;
    while(casi-->0) {
        int n, x, y; cin >> n >> x >> y;
        string s; cin >> s;
        cout << solve(n, x, y, s) << '\n';
    }

    return 0;
}