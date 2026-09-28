#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    ll x, y, k; cin >> x >> y >> k;

    auto gb = [&](ll num, ll base) -> vector<ll> {
        vector<ll> res;
        while(num) {
            res.push_back(num % base);
            num /= base;
        }
        reverse(res.begin(), res.end());
        return res;
    };

    auto bx = gb(x, k);
    auto by = gb(y, k);

    int matches = 0;
    for(int i = 0; i < min(sz(bx), sz(by)); i++) {
        if(bx[i] == by[i]) {
            matches++;
        } else {
            break;
        }
    }

    // cout << "bx : " << bx << " by : " << by << endl;

    int res = sz(bx) - matches + (sz(by) - matches);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}