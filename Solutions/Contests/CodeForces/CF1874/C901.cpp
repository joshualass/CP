#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, m; cin >> n >> m;
    ll g = gcd(n,m);
    n /= g;
    m /= g;
    if(__builtin_popcount(m) > 1) {
        cout << "-1\n";
        return;
    }
    ll start = -1;
    ll moves = 0;
    for(ll i = 31; i >= 0; i--) {
        if(start != -1 && ((n >> i) & 1)) {
            moves += (1 << start) - (1 << i);
        }
        if((m >> i) & 1) start = i;
    }
    cout << moves * g << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}