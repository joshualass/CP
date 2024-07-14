#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    map<array<ll,3>, ll> prev; //{curr value, length, delta}, {count}
    map<array<ll,3>, ll> adds;

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) { //adds for length 2
            adds[{a[i], 2, a[i] - a[j]}]++;
        }

        for(auto [p, c] : prev) {
            if(p[0] + p[2] == a[i]) {
                adds[{a[i], p[1] + 1, p[2]}] += c;
            }
        }
        // cout << "i : " << i << " prev : " << prev << '\n';
        // cout << "i : " << i << " adds : " << adds << '\n';

        for(auto [p, c] : adds) {
            prev[p] = (prev[p] + c) % MOD;
        }
        adds.clear();
    }

    // cout << "final prev : " << prev << '\n';

    vector<ll> res(n + 1);

    for(auto [p, c] : prev) {
        res[p[1]] = (res[p[1]] + c) % MOD;
    }

    cout << n << " ";
    for(int i = 2; i <= n; i++) {
        cout << res[i] << " \n"[i == n];
    }

    return 0;
}