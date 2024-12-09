#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*
    This approach works for prime mod. we want to try and compute this without using modular inverse. 
    int n; cin >> n >> MOD;
    choose(n, n);

    ll res = 0;
    for(int i = 0; i <= n; i++) {
        if(i % 2 == 0) {
            // cout << "i : " << i << " adding : " << inv_fact[i] << '\n';
            res = (res + inv_fact[i]) % MOD;
        } else {
            // cout << "i : " << i << " subtracting : " << inv_fact[i] << '\n';
            res = (res + (MOD - inv_fact[i])) % MOD;
        }
        // cout << "i : " << i << " res : " << res << '\n';
        if(i) {
            // cout << res * fact[i] << " \n"[i == n];
            cout << res * fact[i] << '\n';
        }
    }   
    */

   //just do algebra to get a_n = n * a_{n-1} + (-1)^n

    ll n, MOD; cin >> n >> MOD;
    ll a = 1;
    for(int i = 1; i <= n; i++) {
        a = (a * i + 1 * (i & 1 ? -1 : 1)) % MOD;
        cout << a << " \n"[i == n];
    }

    return 0;
}