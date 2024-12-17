#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<array<ll,2>> a(n);
    for(auto &x : a) cin >> x[1];
    for(auto &x : a) cin >> x[0];
    vector<ll> e(m);
    for(ll &x : e) cin >> x;
    vector<ll> mb(n);
    ll c = 0;
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) {
        c += a[i][1];
        mb[i] = a[i][0] - c;
    }
    for(int i = n - 2; i >= 0; i--) {
        mb[i] = min(mb[i], mb[i+1]);
    }
    // cout << "mb : " << mb << '\n';
    vector<array<ll,2>> res(q);
    for(int i = 0; i < q; i++) {
        cin >> res[i][0];
        res[i][1] = i;
    }
    sort(res.begin(), res.end());
    int p = 0;
    c = 0;
    ll ct = 0;
    vector<ll> et(m);
    for(int i = 0; i < n; i++) {
        while(p != m && c + e[p] <= mb[i]) {
            c += e[p];
            ct += e[p];
            et[p++] = ct;
        }
        ct += a[i][1];
    }
    while(p != m) {
        ct += e[p];
        et[p++] = ct;
    }
    // cout << "et : " << et << '\n';
    p = 0;
    for(int i = 0; i < m; i++) {
        while(p != q && res[p][0] < et[i]) {
            res[p][0] = i;
            p++;
        }
    }
    while(p != q) {
        res[p][0] = m;
        p++;
    }
    sort(res.begin(), res.end(), [](const auto &lhs, const auto &rhs) -> bool {
        return lhs[1] < rhs[1];
    });
    for(int i = 0; i < q; i++) {
        cout << res[i][0] << " \n"[i == q - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}