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

    int n; cin >> n;
    vector<array<ll,2>> a(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = {x, i};
    }

    sort(a.begin(), a.end());

    // cout << "a : " << a << '\n';

    set<int> s;
    s.insert(-1);
    s.insert(n);

    ll cur = 0, delta = 0;
    vector<ll> ud(n + 2);

    for(int i = 0; i < n; i++) {
        auto [val, idx] = a[i];

        // cout << "idx : " << idx << '\n';

        int ld = idx - (*--s.lower_bound(idx));
        int rd = (*s.upper_bound(idx)) - idx;

        // cout << "ld : " << ld << " rd : " << rd << '\n';

        ud[0] += val;
        ud[ld] -= val;
        ud[rd] -= val;
        ud[ld + rd] += val;

        s.insert(idx);
    }

    vector<ll> res;

    for(int i = 0; i < n; i++) {
        delta += ud[i];
        cur += delta;
        res.push_back(cur);
    }

    reverse(res.begin(), res.end());
    for(int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];


    return 0;
}
