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

    ll n, b, p; cin >> n >> b >> p;
    vector<array<ll,2>> a(n);
    for(auto &x : a) {
        for(auto &y : x) {
            cin >> y;
        }
    }

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[1] > rhs[1];
    });

    set<ll> unvis;
    for(ll i = 0; i < n; i++) {
        unvis.insert(i);
    }

    ll best = p;
    ll pt = 0;
    ll cur = p;

    for(ll i = 1; i <= n; i++) {
        ll f = 0;
        while(f == 0 && pt < n) {
            auto [buff, drink] = a[pt++];
            ll latest = min(drink - 1, b - buff - 1);
            auto it = unvis.upper_bound(latest);
            if(it != unvis.begin()) {
                ll turn = *--it;
                unvis.erase(turn);
                cur += drink;
                f = 1;
            }
        }
        if(f == 0) break;

        // cout << "i : " << i << " pt : " << pt << " cur : " << cur << endl;
        best = max(best, cur - i * (i - 1) / 2);
    }

    // cout << "best : " << best << endl;

    int cnt = 0;
    for(auto [buff, drink] : a) {
        if(buff + drink < b + best) cnt++;
    } 

    cout << cnt << '\n';

    return 0;
}
