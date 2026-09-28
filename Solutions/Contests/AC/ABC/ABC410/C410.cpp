#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    ll shift = 0;

    auto get_idx = [&](ll idx) -> ll {

        ll res = (idx + shift) % n;
        if(res < 0) res += n;
        return res;

    };

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int p, x; cin >> p >> x;
            p--;
            ll idx = get_idx(p);
            a[idx] = x;
        } else if(t == 2) {
            int p; cin >> p;
            p--;
            ll idx = get_idx(p);
            cout << a[idx] << '\n';

            // cout << "p : " << p << " shift : " << shift << " a : " << a << '\n';

        } else {
            int k; cin >> k;
            shift += k;
        }
    }

    return 0;
}
