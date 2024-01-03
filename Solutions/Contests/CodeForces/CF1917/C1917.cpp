#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k, d; cin >> n >> k >> d;
    vector<int> v(n);
    vector<int> waters(k);
    for(auto &x : v) cin >> x;
    for(auto &x : waters) cin >> x;
    int ans = 0;
    for(int i = 0; i < min(d,4001); i++) {
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            if(v[j] == j + 1) cnt++;
        }
        ans = max(ans,cnt + (d - 1 - i) / 2);
        for(int j = 0; j < waters[i % k]; j++) {
            v[j]++;
        }
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