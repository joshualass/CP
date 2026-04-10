#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    set<ll> res;

    auto add = [&](ll cnt) -> void {
        assert(n % cnt == 0);
        ll len = n / cnt;
        res.insert(cnt * (n - len + 1 + 1) / 2);
    };

    for(ll i = 1; i * i <= n; i++) {
        if(n % i == 0) {
            add(i);
            add(n / i);
        }
    }
    
    for(auto &x : res) cout << x << " ";
    cout << '\n';

    return 0;
}
