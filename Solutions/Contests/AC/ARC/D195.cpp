#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int inf = 1e9;

    map<array<int,2>, int> dp;

    dp[{inf,inf}] = 0;

    for(int i = 0; i < n; i++) {

        map<array<int,2>,int> ndp;

        for(auto [st, v] : dp) {
            auto [elim, prev] = st;

            //no swap
            array<int,2> nx = {prev, a[i]};
            int nxval = v + (elim != prev);

            if(ndp.count(nx) == 0 || nxval < ndp[nx]) {
                ndp[nx] = nxval;
            }

            //try swap
            nx = {a[i], prev};
            nxval = v + 1 + (elim != a[i]);

            if(ndp.count(nx) == 0 || nxval < ndp[nx]) {
                ndp[nx] = nxval;
            }
        }

        int lo = INT_MAX;
        for(auto [st, v] : ndp) {
            lo = min(lo, v + (st[0] != st[1]));
        }

        for(auto it = ndp.begin(); it != ndp.end();) {
            auto [st,v] = *it;
            if(v + (st[0] != st[1]) > lo) {
                it = ndp.erase(it);
            } else {
                it++;
            }
        }

        dp = ndp;

    }

    int lo = INT_MAX;
    for(auto [st, v] : dp) {
        lo = min(lo, v + (st[0] != st[1]));
    }    

    cout << lo << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}