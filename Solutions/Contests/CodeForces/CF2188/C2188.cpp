#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> b = a;
    sort(b.begin(), b.end());
    if(a == b) {
        cout << "-1\n";
        return;
    }

    int mn = *min_element(a.begin(), a.end());
    int mx = *max_element(a.begin(), a.end());

    int res = INT_MAX;

    for(int i = 0; i < n; i++) {
        if(a[i] != b[i]) {
            res = min(res, max(mx - a[i], a[i] - mn));
        }
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