#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> a(n);
    vector<ll> b(n);

    for(auto &x : a) cin >> x;
    for(auto &x: b) cin >> x;

    ll sum = reduce(b.begin(), b.end());

    set<ll> s(b.begin(), b.end());

    ll best = INT_MAX;

    for(int i = 0; i < n; i++) {
        if(a[i] > sum) continue;
        if(s.upper_bound(a[i]) != s.end()) {
            ll baklavas = *s.upper_bound(a[i]);
            best = min(best, baklavas - a[i]);
        }
        if(s.upper_bound(a[i]) != s.begin()) {
            ll baklavas = (*--s.upper_bound(a[i]));
            best = min(best, a[i] - baklavas);
        }
    }

    cout << (best == INT_MAX ? -1LL : best) << '\n';

    return 0;
}