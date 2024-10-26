#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    k = n - k;
    int res = INT_MAX;
    for(int i = 0; i + k - 1 < n; i++) {
        res = min(res, a[i+k-1]-a[i]);
    }
    cout << res << '\n';
    return 0;
}