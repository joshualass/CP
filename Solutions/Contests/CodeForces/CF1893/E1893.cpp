#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int m; cin >> m;

    vector<ll> n(m);
    vector<ll> l(m);
    vector<ll> r(m);

    vector<vector<ll>> a(m);
    vector<vector<ll>> c(m);

    ll lo = 0, hi = 0;
    map<ll,ll> mins;

    for(int i = 0; i < m; i++) {
        cin >> n[i] >> l[i] >> r[i];
        lo += l[i];
        hi += r[i];
        a[i].resize(n[i]);
        c[i].resize(n[i]);
        ll sum = 0;
        for(int j = 0; j < n[i]; j++) {
            cin >> a[i][j];
        }
        for(int j = 0; j < n[i]; j++) {
            cin >> c[i][j];
            sum += c[i][j];
        }

        for(int j = 0; j < n[i]; j++) {
            if(l[i] > sum - c[i][j]) {
                mins[a[i][j]] += l[i] - (sum - c[i][j]);
            }
        }
    }

    ll best = -1;
    ll bestmin = INT_MAX;

    for(ll i = lo; i <= hi; i++) {
        ll v = mins[i];
        cout << "i : " << i << " v : " << v << '\n';
        if(v < bestmin) {
            best = i;
            bestmin = v;
        }
        if(v == 0) {
            break;
        }
    }
    cout << bestmin << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}