#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll l, r; cin >> l >> r;

    ll most = 0;
    pair<ll,ll> best = {-1,-1};

    for(ll i = l; i < l + 1000; i++) {
        for(ll j = r - 1000; j <= r; j++) {
            if(gcd(i,j) == 1 && j - i > most) {
                most = j - i;
                best = {i,j};
            }
        }
    }

    // cout << best.first << " " << best.second << '\n';
    cout << most << "\n";

    return 0;
}