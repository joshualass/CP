#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, c, d; cin >> n >> c >> d;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll cost = 0;

    if(d <= c) {
        for(int i = 0; i < n; i++) {
            cost += abs(a[i]) * d;
        }
        a.assign(n,0);
    } else if(d >= c * 2) {
        ll prev = 0;
        for(int i = 0; i < n; i++) {
            cost += abs(prev -  a[i]) * c;
            prev = a[i];
        }
    } else {

        ll prev = 0;
        for(int i = 0; i + 1 < n; i++) {
            int go_left = max(0LL, a[i] - max(prev, a[i+1]));
            a[i] -= go_left;
            cost += go_left * d;

            int go_right = max(0LL, min(prev, a[i+1]) - a[i]);
            a[i] += go_right;
            cost += go_right * d;
        }

        for(int i = 0; i < n; i++) {
            cost += abs(prev -  a[i]) * c;
            prev = a[i];
        }
    }

    cout << cost << '\n';
    for(int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }

    return 0;
}
