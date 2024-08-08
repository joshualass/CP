#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//harmonic series is logn ...

void solve() {
    
    int n; cin >> n;
    vector<bool> in(n + 1);
    vector<int> cnts(n + 1,1);
    vector<int> a(n+1);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        in[num] = 1;
        a[num]++;
    }

    ll res = 0;
    for(int i = 1; i <= n; i++) {
        if(in[i]) {
            int cnt = cnts[i];
            int sum = 0;
            for(int j = 1; j * i <= n; j++) {
                cnts[i * j] -= cnt;
                sum += a[i * j];
                in[i * j] = 1;
            }
            // cout << "i : " << i << " cnt : " << cnt << " sum : " << sum << " add to res : " << 1LL * cnt * sum * (sum - 1) / 2 << '\n';
            res += 1LL * cnt * sum * (sum - 1) / 2;
        }
    }

    cout << 1LL * n * (n - 1) / 2 - res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}