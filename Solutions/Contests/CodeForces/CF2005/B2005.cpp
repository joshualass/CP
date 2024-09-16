#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m, q; cin >> n >> m >> q;
    set<int> s;
    for(int i = 0; i < m; i++) {
        int b; cin >> b;
        s.insert(b);
    }
    for(int i = 0; i < q; i++) {
        int a; cin >> a;
        if(s.lower_bound(a) == s.end()) {
            int lo = (*--s.lower_bound(a));
            cout << n - lo << '\n';
        } else if(s.lower_bound(a) == s.begin()) {
            int hi = (*s.lower_bound(a));
            cout << hi - 1 << '\n';
        } else {
            int lo = (*--s.lower_bound(a));
            int hi = (*s.lower_bound(a));

            cout << (hi - lo) / 2 << '\n';

        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}