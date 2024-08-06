#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//harmonic series is logn ...

const int N = 1e6 + 1;
void solve() {
    
    int n; cin >> n;
    vector<int> a(n + 1);
    vector<bool> in(n + 1);
    ll res = 1LL * n * (n - 1) / 2;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[num]++;
        in[num] = 1;
    }
    for(int i = 1; i <= n; i++) {
        if(in[i]) {
            ll cnt = 0;
            for(int j = 1; j * i <= n; j++) {
                cnt += a[i * j];
                in[i * j] = 0;
            }
            cout << "i : " << i << " cnt : " << cnt << '\n';
            res -= cnt * (cnt - 1) / 2;
        }
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}