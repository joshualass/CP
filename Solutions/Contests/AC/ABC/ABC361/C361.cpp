#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<int> b(n);
    for(int &x : b) cin >> x;

    sort(b.begin(), b.end());

    int res = INT_MAX;

    for(int i = 0; i + n - k - 1 < n; i++) {
        res = min(res, b[i + n - k - 1] - b[i]);
    }

    cout << res << '\n';

    return 0;
}