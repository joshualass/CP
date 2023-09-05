#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll dp1[1000001];
ll dp2[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dp1[0] = 2;
    dp1[1] = 2;
    dp2[0] = 5;
    dp2[1] = 5;

    for(int i = 2; i <= 1000000; i++) {
        dp1[i] = (dp1[i-2] * 2) % MOD;
        dp2[i] = (dp2[i-2] * 5) % MOD;
    }

    int l, r; cin >> l >> r;

    ll ans = 0;
    for(int i = l-1; i <= r-1; i++) {
        ans += dp1[i];
        ans += dp2[i];
    }
    cout << (ans % MOD);

    return 0;
}