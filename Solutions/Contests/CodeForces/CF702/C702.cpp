#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> a(n), b(m);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;    
    b.push_back(-1e18);
    b.push_back(1e18);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll r = 0;
    int p = 0;
    for(int i = 0; i < n; i++) {
        while(p != b.size() - 1 && abs(b[p+1] - a[i]) <= abs(b[p] - a[i])) p++;
        r = max(r, abs(b[p] - a[i]));
    }

    cout << r << '\n';

    return 0;
}