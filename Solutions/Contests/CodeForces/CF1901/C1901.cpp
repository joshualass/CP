#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;

    ll hi = 0;
    ll lo = LLONG_MAX;

    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        lo = min(lo,num);
        hi = max(hi,num);
    }
    vector<int> ops;
    while(lo != hi) {
        // cout << "hi : " << hi << " lo : " << lo << '\n';
        if(hi & 1) {
            ops.push_back(0);
        } else {
            ops.push_back(1);
            lo++; hi++;
        }
        lo >>= 1;
        hi >>= 1;
    }
    cout << ops.size() << '\n';
    if(ops.size() <= n) {
        for(auto x : ops) cout << x << " ";
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}