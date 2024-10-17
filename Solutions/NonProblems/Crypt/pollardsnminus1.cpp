#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD;

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll N; cin >> N;
    MOD = N;

    ll a = 2;
    ll n = 1;


    while(1) {
        a = binexp(a,n);
        if(gcd(a - 1, N) > 1 && gcd(a-1, N) < N) {
            break;
        }
        n++;
    }

    cout << "a : " << a - 1 << " n : " << n << '\n';

    cout << "g : " << gcd(a-1, N) << '\n';


    return 0;
}