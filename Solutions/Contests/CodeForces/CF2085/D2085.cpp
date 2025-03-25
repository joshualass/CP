#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<array<ll,2>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
        a[i][1] = i;
    }   
    set<int> s;
    for(int i = n - k - 1; i >= 0; i -= k + 1) {
        s.insert(i);
    }
    ll res = 0;
    sort(a.rbegin(), a.rend());
    for(auto [d, i] : a) {
        if(s.lower_bound(i) != s.end()) {
            res += d;
            s.erase(s.lower_bound(i));
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