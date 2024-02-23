#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    sort(v.begin(), v.end());
    int ans = 0;
    for(int i = 0; i < n; i++) {
        ans = max(ans, min(n - i, v[i]));
    }
    cout << ans << '\n';
    return 0;
}