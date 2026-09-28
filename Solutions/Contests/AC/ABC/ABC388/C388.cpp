#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    ll res = 0;
    for(int i = 0; i < n; i++) {
        int l = i + 1, r = n;
        while(l != r) {
            int m = (l + r) / 2;
            if(a[i] * 2 <= a[m]) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        res += n - l;
    }

    cout << res << '\n';

    return 0;
}