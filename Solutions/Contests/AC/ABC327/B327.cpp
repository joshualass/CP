#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    ll num = -1;
    for(ll i = 1; true; i++) {
        ll val = 1;
        for(int j = 0; j < i; j++) {
            val *= i;
        }
        if(val == n) num = i;
        if(val > n) break;
    }
    cout << num << '\n';

    return 0;
}