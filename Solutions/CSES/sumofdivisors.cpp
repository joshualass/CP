#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    ll cnt = 0;
    if(n % 2 == 0) {
        cnt = ((n / 2) % MOD) * ((n + 1) % MOD);
    } else {
        cnt = (n % MOD) * (((n + 1) / 2) % MOD);
    }
    // cout << "first: " << cnt << "\n";
    for(int i = 1; i * i <= n; i++) {
        // ll add = (i * (n % MOD) / i) - i;
        ll add = (((n / i) * i % MOD) - i + MOD) % MOD;
        // cout << "adding: " << add << " i: " << i << "\n";
        cnt += add;
        cnt %= MOD;
    }

    cout << cnt << "\n";

    return 0;
}