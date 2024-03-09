#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    ll l = 1, r = n * n;
    while(l < r) {
        ll m = (l + r) / 2;
        // cout << "m: " << m << "\n";
        ll below = 0;
        ll at = 0;
        // cout << "m: " << m << "\n";
        for(int i = 1; i <= n; i++) {
            // bool in = m % i == 0;
            // below += m / i - in;
            // at += in;
            bool in = m % i == 0 && m / i <= n;
            below += min(n,m / i) - in;
            at += in;
            // cout << "i: " << i << " in: " << in << " below: " << below << "\n";
        }
        // cout << "m: " << m << " below: " << below << " at: " << at << "\n";
        if(at + below <= n * n / 2) {
            l = m + 1;
        } else if(below >= n * n / 2 + 1) {
            r = m;
        } else {
            l = r = m;
        }

    }
    cout << l << "\n";
    return 0;
}