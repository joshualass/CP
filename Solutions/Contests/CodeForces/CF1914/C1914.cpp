#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    vector<int> b(n);

    for(auto &x: a) cin >> x;
    for(auto &x: b) cin >> x;

    int ans = 0;
    int curr = 0;
    int mostsub = 0;
    for(int i = 0; i < n; i++) {
        if(k == 0) break;
        curr += a[i];
        mostsub = max(mostsub, b[i]);
        k--;
        ans = max(ans, curr + mostsub * k);
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}