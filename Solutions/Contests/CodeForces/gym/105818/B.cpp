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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<array<ll,2>> a;
    ll lo = LLONG_MAX, hi = LLONG_MIN;
    for(int i = 0; i < n; i++) {
        ll r, c; cin >> r >> c;
        a.push_back({c, r + c});
        lo = min(lo, c);
        hi = max(hi, r + c);
    }
    
    sort(a.begin(), a.end());

    // cout << "a : " << a << '\n';

    vector<array<ll,2>> b;
    for(auto [left, right] : a) {
        if(b.empty() || left > b.back()[1]) {
            b.push_back({left, right});
        } else {
            b.back()[1] = max(b.back()[1], right);
        }
    }
    // cout << "b : " << b << '\n';

    ll res = hi - lo;
    vector<ll> gaps;
    for(int i = 1; i < b.size(); i++) {
        gaps.push_back(b[i][0] - b[i-1][1]);
    }
    sort(gaps.begin(), gaps.end());
    for(int i = 0; i < n; i++) {
        cout << res << " \n"[i == n - 1];
        if(gaps.size()) {
            res -= gaps.back();
            gaps.pop_back();
        }
    }

    return 0;
}
