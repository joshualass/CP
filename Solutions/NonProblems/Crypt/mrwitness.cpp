#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD = 1e9 + 7;

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

    int p; cin >> p;
    for(int i = 2; i <= 2; i++) {
        if(p % 2 == 0 || gcd(i,p) > 1 && gcd(i,p) < p) {
            cout << "step 1 composite : " << i << '\n';
            continue;
        }
        int q = p - 1, k = 0;
        while(q % 2 == 0) {
            k++;
            q /= 2;
        }
        cout << "q : " << q << " k : " << k << '\n';
        MOD = p;
        ll a = binexp(i,q);
        cout << "a : " << a << '\n';
        if(a == 1) {
            // cout << "not a witness 4 : " << i << '\n';
            continue;
        }
        bool iswitness = 1;
        for(int j = 0; j < k; j++) {
            cout << "a : " << a << '\n';
            if(a == p - 1) {
                cout << "not a witness 6 : " << i << "\n";
                iswitness = 0;
                break;
            }
            a = a * a % MOD;
        }
        if(iswitness) {
            cout << "is witness 9 : " << i << '\n';
        }
    }

    return 0;
}