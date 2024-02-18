#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<int> rows(n);
    vector<int> cols(n);

    for(int i = 0; i < n;i ++) {
        cin >> rows[i] >> cols[i];
    }
    sort(rows.begin(), rows.end());
    sort(cols.begin(), cols.end());
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += abs(rows[i-1] - i);
        ans += abs(cols[i-1] - i);
    }
    cout << ans << '\n';
    return 0;
}