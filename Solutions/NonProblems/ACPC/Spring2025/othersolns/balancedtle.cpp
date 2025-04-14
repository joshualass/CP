#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) {
        string t; cin >> t;
        cin >> x;
    }

    int res = INT_MAX;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            res = min(res, abs(a[i] - a[j]));
        }
    }

    cout << res << '\n';

    return 0;
}
