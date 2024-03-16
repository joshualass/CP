#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<vector<ll>> a(n);
    for(int i = 0; i < n; i++) {
        int b, c; cin >> b >> c;
        a[b].push_back(c);
    }
    priority_queue<ll,vector<ll>,greater<ll>> pq;
    ll below = n;
    ll res = 0;
    ll cnt = 0;
    for(ll i = n - 1; i >= 0; i--) {
        if(a[i].empty()) continue;
        for(ll x : a[i]) {
            pq.push(x);
        }
        below -= a[i].size();
        while(below + cnt < i) {
            ll x = pq.top();
            pq.pop();
            res += x;
            cnt++;
        }
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