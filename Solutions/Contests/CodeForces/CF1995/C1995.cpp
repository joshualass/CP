#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll getsq(ll x) {
    ll n = sqrt(x);
    while(n * n < x) n++;
    while(n * n > x) n--;
    return n;
}

void solve() {
    int n; cin >> n;
    
    ll res = 0;
    ll prevops = 0;
    ll prev = 1;

    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        if(a == 1 && prev > 1) {
            cout << "-1\n";
            for(int j = i + 1; j < n; j++) cin >> a;
            return;
        }
        ll cops = 0;

        while(prev < a && prev != 1) {
            cops--;
            prev *= prev;
        }
        ll starta = a;
        while(a < prev) {
            cops++;
            a *= a;
        }

        ll doops = max(0LL, cops + prevops);
        res += doops;
        prevops = doops;
        prev = starta;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}