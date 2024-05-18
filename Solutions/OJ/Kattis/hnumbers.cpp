#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<bool> isprime(1e6 + 2,1);
    vector<bool> issemiprime(1e6 + 2);

    for(ll i = 5; i <= 1e6 + 1; i += 4) {
        // if(isprime[i] == 0) continue;
        for(ll j = 5; j * i <= 1e6 + 1 && j <= i; j += 4) {
            if(isprime[i] && isprime[j]) {
                // if(i * j < 1000) {
                //     cout << "add semiprime : " << i << " " << j << ": " << i * j << '\n';
                // }
                issemiprime[i*j] = 1;
            }
            // if(i * j < 1000) {
            //     cout << "not prime : " << i * j << '\n';
            // }
            isprime[i*j] = 0;
        }
    }

    vector<int> pref(1e6 + 2);
    for(int i = 1; i < 1e6 + 2; i++) {
        pref[i] = pref[i-1] + issemiprime[i];
    }

    // for(int i = 0; i < 1000; i++) {
    //     if(issemiprime[i]) {
    //         for(ll j = 5; j <= i; j += 4) {
    //             for(ll k = 5; j * k <= i; k += 4) {
    //                 if(j * k == i && (isprime[j] == 0 || isprime[k] == 0)) {
    //                     cout << "should not be semiprime: " << i << '\n';
    //                 }
    //             }
    //         }
    //     }
    // }

    int n; cin >> n;
    while(n != 0) {
        cout << n << " " << pref[n] << '\n';
        cin >> n;
    }
    return 0;
}