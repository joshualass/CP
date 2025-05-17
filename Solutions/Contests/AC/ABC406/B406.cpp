#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    ll res = 1;

    ll s = 1;
    for(int i = 0; i < k; i++) s *= 10;

    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        if(s / x < res) {
            res = 1;
        } else {
            res *= x;
            if(res >= s) res = 1;
        }
        // cout << "i : " << i << " res : " << res << '\n';
    }

    cout << res << '\n';

    return 0;
}
