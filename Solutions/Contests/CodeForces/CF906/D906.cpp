#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll n, c; cin >> n >> c;

    ll sum; cin >> sum;

    vector<pair<ll,ll>> v(n-1);

    for(int i = 1; i < n; i++) {
        ll num; cin >> num;
        v[i-1] = {(i + 1) * c - num, num};

    }

    sort(v.begin(),v.end());
    bool ok = true;
    for(int i = 0; i < n - 1; i++) {
        if(sum >= v[i].first) {
            sum += v[i].second;
        } else {
            ok = false;
        }
    }
    cout << (ok ? "Yes" : "No") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}