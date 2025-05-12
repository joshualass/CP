#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> l(n + 1, n), r(n + 1, n);
    set<int> s;
    for(int i = 1; i <= n; i++) s.insert(i);

    for(int i = 0; i < n; i++) {
        if(s.upper_bound(a[i]) != s.begin()) {
            s.erase(*--s.upper_bound(a[i]));
        }
        l[n - s.size()] = min(l[n - s.size()], i + 1);
    }

    for(int i = 1; i <= n; i++) s.insert(i);
    for(int i = n - 1; i >= 0; i--) {
        if(s.upper_bound(a[i]) != s.begin()) {
            s.erase(*--s.upper_bound(a[i]));
        }
        r[n - s.size()] = min(r[n - s.size()], n - i);
    }

    ll res = 0;
    for(int i = 0; i < n; i++) {
        if(l[i] + r[i] <= n) {
            res += n - l[i] - r[i] + 1;
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