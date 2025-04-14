#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l; cin >> n >> l;
    vector<ld> a(n);
    for(ld &x : a) cin >> x;
    sort(a.begin(), a.end());

    ld res = max(a[0], l - a[n-1]);
    for(int i = 1; i < n; i++) {
        res = max(res, (a[i] - a[i-1]) / 2);
    }
    cout << fixed << setprecision(10) << res << '\n';
    return 0;
}
