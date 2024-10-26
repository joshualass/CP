#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    
    ll n, k; cin >> n >> k;

    ll prev = 1, next = 1;

    ll idx = 1;
    while(1) {
        if(prev % k == 0) {
            break;
        }
        idx++;
        ll nn = (next + prev) % k;
        prev = next;
        next = nn;
    }

    cout << n % MOD * idx % MOD << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}