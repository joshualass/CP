#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> ans(n);
    for(int i = 0; i < n; i += 2) {
        ans[i] = i / 2 + 1;
    }
    for(int i = 1; i < n; i += 2) {
        ans[i] = n - i / 2;
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n -1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}