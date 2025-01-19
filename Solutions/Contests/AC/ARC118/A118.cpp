#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t, n; cin >> t >> n;
    n--;
    set<ll> s;
    for(ll i = 1; i <= 100; i++) {
        s.insert(i * (100 + t) / 100);
    }
    ll misscnt = 100 + t - s.size();
    ll cycles = n / misscnt;
    ll left = 0;
    n -= cycles * misscnt;
    for(ll i = 1; i <= t + 100; i++) {
        if(s.count(i) == 0) {
            if(n == 0) {
                left = i;
                break;
            }
            n--;
        }
    }

    // cout << "mc : " << misscnt << " cycles : " << cycles << " left : " << left << '\n';

    cout << (t + 100) * cycles + left << '\n';

    return 0;
}