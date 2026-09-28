#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d; cin >> n >> d;

    vector<array<int,2>> a(n);
    for(auto &x : a) cin >> x[0] >> x[1];
    for(int k = 1; k <= d; k++) {
        int hi = a[0][0] * (a[0][1] + k);
        for(int i = 1; i < n; i++) {
            hi = max(hi, a[i][0] * (a[i][1] + k));
        }
        cout << hi << '\n';
    }

    return 0;
}