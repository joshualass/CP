#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q; cin >> q;

    deque<array<ll,2>> dq;

    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int c, x; cin >> c >> x;
            dq.push_back({c, x});
        } else {
            ll k; cin >> k;
            ll res = 0;
            while(k) {
                ll mv = min(k, dq.front()[0]);
                k -= mv;
                res += mv * dq.front()[1];
                array<ll,2> z = dq.front();
                dq.pop_front();
                z[0] -= mv;
                if(z[0]) dq.push_front(z);
            }

            cout << res << '\n';

        }
    }

    return 0;
}
