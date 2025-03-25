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

ll choose(int n, int k) {
    ll num = 1;

    for (ll i = 2; i <= n; ++i) {
        num = (num * i) % MOD;
    }

    ll kf = 1;
    for (ll i = 2; i <= k; ++i) {
        kf = (kf * i) % MOD;
    }

    ll kmi = 1;
    for (ll i = 2; i <= n - k; ++i) {
        kmi = (kmi * i) % MOD;
    }

    ll cnt = (num * exp(kf, MOD - 2)) % MOD;
    cnt = (cnt * exp(kmi, MOD - 2)) % MOD;

    return cnt % MOD;
    
}

ll fact(int n) {
    ll cnt = 1;
    for (ll i = 2; i <= n; ++i) {
        cnt = (cnt * i) % MOD;
    }
    return cnt;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t; cin >> n >> t;

    vector<int> a(n);
    for (auto& x : a)
        cin >> x;
    
    int fat = t;
    for (auto x : a)
        fat -= x;
    
    // cerr << "fat : " << fat << endl;
    
    ll cnt = choose(n + fat + 1, fat) % MOD;

    cerr << "choo : " << cnt << endl;

    cnt = (cnt * fact(n)) % MOD;

    // cnt = (cnt * exp(t, n)) % MOD;

    cout << cnt << endl;

    return 0;
}
