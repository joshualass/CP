#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<ll> p(n + 1);
    for(int i = 0; i < n; i++) {
        p[i+1] = a[i] + p[i];
    }

    ll res = 0;

    map<int,int> m;
    for(int i = k + 1; i <= n; i++) {
        m[p[i-(k+1)] % k]++;
        res += m[p[i] % k];
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