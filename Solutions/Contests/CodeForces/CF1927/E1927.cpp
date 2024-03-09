#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> ans(n);
    int lo = 1;
    for(int i = 0; i < k; i += 2) {
        for(int j = i; j < n; j += k) {
            ans[j] = lo++;
        }
    }
    int hi = n;
    for(int i = 1; i < k; i += 2) {
        for(int j = i; j < n; j += k) {
            ans[j] = hi--;
        }
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}