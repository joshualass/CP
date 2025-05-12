#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

array<ll,2> solve1(ll l, ll r) {
    for(ll d = r - l; d >= 0; d--) {
        for(ll a = l; a + d <= r; a++) {
            ll b = a + d;
            if(gcd(a,b) == 1) return {a,b};
        }
    }
    return {-1,-1};
}

void solve() {

    ll l, r, g; cin >> l >> r >> g;

    ll r1 = r / g;
    ll l1 = (l + g - 1) / g;
    auto [a, b] = solve1(l1, r1);
    if(a == -1) {
        cout << "-1 -1\n";
    } else {
        cout << a * g << " " << b * g << '\n';
    }
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}