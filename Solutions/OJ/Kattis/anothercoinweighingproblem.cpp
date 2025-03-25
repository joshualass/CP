#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD = 998244353;

ll exp(ll b, ll p) {
    ll cnt = 1;
    while (p) {

        if (p % 2 == 1) {
            cnt = (cnt * b) % MOD;
        }

        b = (b * b) % MOD;
        p >>= 1;
        
    }
    return cnt;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll m, k; cin >> m >> k;

    vector<ll> a(k+1);

    for (int i = k; i; --i) {
        a[i] = (exp((k / i)*2 + 1, m) - 1) % MOD;
        for (int j = 2*i; j <= k; j += i)
            a[i] = (a[i] - a[j] + MOD) % MOD;
    }

    cout << (a[1] + 1) % MOD << endl;

    return 0;
}
