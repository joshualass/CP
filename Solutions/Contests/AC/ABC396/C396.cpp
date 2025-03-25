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

    int n, m; cin >> n >> m;
    vector<ll> a(n), b(m);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    a.insert(a.begin(), 0);

    ll cur = 0;
    for(int i = 1; i <= n; i++) {
        cur += a[i];
        a[i] = cur;
    }    
    for(int i = n - 1; i >= 0; i--){
        a[i] = max(a[i], a[i+1]);
    }

    cur = 0;

    ll res = a[0];
    for(int i = 0; i < m && i < n; i++) {
        cur += b[i];
        res = max(res, cur + a[i+1]);
    }

    cout << res << '\n';

    return 0;
}