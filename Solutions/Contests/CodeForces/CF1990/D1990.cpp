#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//if a_i is >= 5, it will never be better to do operation of type 1

void solve() {
    
    int n; cin >> n;

    ll lo = 1, hi = 1, none = 0;

    for(int i = 1; i <= n; i++) {

        ll a; cin >> a;

        ll nextnone = -1, nexthi = -1, nextlo = -1;

        if(a <= 0) {
            nextnone = none;
            nexthi = MOD;
            nextlo = MOD;
        } else if(a <= 2) {
            nextnone = min(none + 1, lo);
            nextlo = none + 1;
            nexthi = MOD;
        } else if(a <= 4) {
            nextlo = hi + 1;
            nexthi = lo + 1;
            nextnone = none + 1;
        } else {
            nextnone = 1 + min({lo, hi, none});
            nextlo = MOD;
            nexthi = MOD;
        }
        lo = nextlo;
        hi = nexthi;
        none = nextnone;

        // cout << "i : " << i << " lo : " << lo << " hi : " << hi << " none : " << none << '\n';
    }

    cout << none << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}