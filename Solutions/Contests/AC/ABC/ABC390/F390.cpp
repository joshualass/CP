#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<set<int>> idxs(n);
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        idxs[a[i]].insert(i);
    }

    ll res = 0;

    for(int i = 0; i < n; i++) {
        int lo = -1, hi = n;
        if(idxs[a[i]].lower_bound(i) != idxs[a[i]].begin()) {
            lo = max(lo, *--idxs[a[i]].lower_bound(i));
        }
        if(a[i] + 1 < n && idxs[a[i] + 1].lower_bound(i) != idxs[a[i] + 1].begin()) {
            lo = max(lo, *--idxs[a[i] + 1].lower_bound(i));
        }
        if(a[i] + 1 < n && idxs[a[i] + 1].upper_bound(i) != idxs[a[i] + 1].end()) {
            hi = min(hi, *idxs[a[i] + 1].upper_bound(i));
        }
        res += 1LL * (i - lo) * (hi - i);
    }

    cout << res << '\n';

    return 0;
}