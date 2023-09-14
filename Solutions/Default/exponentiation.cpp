#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    while(n-->0) {
        ll a, b;
        cin >> a >> b;
        ll ans = 1;
        ll mult = a;
        while(b != 0) {
            if(b & 1) {
                ans *= mult;
                ans %= mod;
            }
            b >>= 1;
            mult *= mult;
            mult %= mod;
        }
        cout << ans << "\n";
    }

    return 0;
}