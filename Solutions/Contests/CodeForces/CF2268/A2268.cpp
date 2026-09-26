#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<ll> p(n + 1);
    for(int i = 0; i < n; i++) {
        p[i+1] = p[i] + a[i];
    }

    ll res = 0;
    if(n >= (k - 1) * 2) {
        res = p[n - k + 1] - p[k - 1];
    }

    // cout << "res part : " << res << endl;

    for(int i = 0; i <= min(n - k, k - 2); i++) {
        res += max(a[i], a[n - i - 1]);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}