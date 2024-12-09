#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, c; cin >> n >> c;
    vector<ll> a(n);
    for (auto& x : a)
        cin >> x;
    
    vector<bool> dp(c+1);

    dp[0] = 1;
    bool works = false;

    vector<ll> twos = {1};

    for (int i = 0; i < 61; ++i) {
        twos.push_back(twos.back() * (ll)2);
    }


    for (int i = 0; i < 61; ++i) {
        ll two = twos[i];

        vector<bool> new_dp(c+1);

        for (int j = 0; j < n; ++j) {
            ll contri = a[j] / two;
            if ((a[j] % two) != 0)
                contri++;

            for (ll k = contri; k <= c; ++k) {

                if (contri == 1 && (dp[k])) {
                    works = true;
                }
                
                if (dp[k - contri])
                    new_dp[k] = true;
            }
        }
        
        swap(dp, new_dp);
        if (dp[c]) {
            works = true;
        }
    }

    if (works)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}