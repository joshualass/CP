#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> d(n - 1);
    for(int i = 1; i < n; i++) {
        d[i - 1] = (a[i] - a[i-1] + m) % m;
    }

    // cout << "d : " << d << endl;

    vector<int> d2;
    for(int i = 1; i * 2 <= sz(d); i++) {
        d2.push_back((d[i-1] + d[sz(d) - i]) % m);
    }
    if(sz(d) & 1) d2.push_back(d[sz(d) / 2]);
    
    // cout << "d2 : " << d2 << endl;

    sort(d2.begin(), d2.end());

    ll res = LLONG_MAX;
    vector<ll> suf(sz(d2) + 1);
    for(int i = sz(d2) - 1; i >= 0; i--) {
        suf[i] = (m - d2[i]) % m + suf[i+1];
    }

    ll down = 0;
    for(int i = -1; i < sz(d2); i++) {
        if(i >= 0) down += d2[i];
        ll up = suf[i + 1];
        res = min(res, max(up, down));
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}