#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    
    vector<ll> d(n);
    for(ll &x : d) cin >> x;

    sort(d.begin(), d.end());

    vector<ll> diffs;
    for(int i = 1; i < n; i++) diffs.push_back(d[i] - d[i-1]);

    ll res = d.back() - d.front();

    sort(diffs.rbegin(), diffs.rend());

    for(int i = 0; i < diffs.size() && m - 1 > 0; i++) {
        res -= diffs[i];
        m--;
    }

    cout << res << '\n';

    return 0;
}
