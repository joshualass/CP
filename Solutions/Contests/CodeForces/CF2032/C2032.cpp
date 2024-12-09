#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    int hi = 0;
    int res = INT_MAX;
    for(int i = 0; i < n - 1; i++) {
        while(hi != n - 1 && a[hi+1] < a[i] + a[i+1]) {
            hi++;
        }
        res = min(res, n - (hi - i + 1));
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