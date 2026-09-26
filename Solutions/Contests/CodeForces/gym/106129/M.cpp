#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, d; cin >> n >> d;
    vector<vector<int>> m(n + 1);
    for(int i = 0; i < n; i++) {
        int p; cin >> p;
        m[p].push_back(i);
    }

    int res = 0;
    while(1) {
        ll l, r;
        int ok = 1;
        for(int i = 0; i < sz(m[res]); i++) {
            if(i == 0) {
                r = m[res][i];
                l = max(0LL, m[res][i] - d + 1);
            } else {
                int x = m[res][i];
                if(x - r + 1 <= d) {
                    l = max(l, x - d + 1);
                } else if(x >= l + d * 2) {
                    ll nl = max(x - d + 1, l + d * 2);
                    ll nr = x ;
                    l = nl;
                    r = nr;
                } else {
                    ok = 0;
                    break;
                }
            }
        }

        if(ok) {
            cout << res << '\n';
            return 0;
        }
        res++;
    }

    return 0;
}
