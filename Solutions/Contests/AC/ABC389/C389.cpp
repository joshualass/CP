#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q; cin >> q;
    deque<ll> dq;
    ll f = 0;

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll l; cin >> l;
            if(dq.size()) {
                dq.push_back(dq.back() + l);
            } else {
                dq.push_back(l);
            }
        } else if(type == 2) {
            f = dq.front();
            dq.pop_front();
        } else {
            ll k; cin >> k;
            k -= 2;
            if(k < 0) {
                cout << 0 << '\n';
            } else {
                cout << dq[k] - f << '\n';
            }
        }
    }


    return 0;
}