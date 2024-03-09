#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> pref(n + 1);
    vector<ll> sums(n + 1);
    for(int i = 1; i <= n; i++) {
        int num; cin >> num;
        pref[i] = pref[i-1];
        sums[i] = sums[i-1];
        sums[i] += num;
        if(num == 1) pref[i]++;
    }
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        int ones = pref[r] - pref[l-1];
        int twos = r - l + 1 - ones;
        int minsum = ones * 2 + twos;
        // cout << "i : " << i << " ms : " << minsum << '\n';
        // cout << "r - l? " << sums[r] - sums[l-1] << '\n';
        if(minsum > sums[r] - sums[l-1] || r - l == 0) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
        }

        
        // if((r - l + 1 - cnt) * 2 >= r - l + 1 && r - l != 0) {
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}