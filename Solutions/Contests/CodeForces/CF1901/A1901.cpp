#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, x; cin >> n >> x;
    int prev = 0;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        ans = max(ans, num - prev);
        prev = num;
    }
    ans = max((x-prev)*2,ans);
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}