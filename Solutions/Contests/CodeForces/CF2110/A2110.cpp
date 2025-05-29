#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    if((a.back() - a.front()) & 1) {
        int res = n;
        for(int i = 1; i < n; i++) {
            if((a[i] - a[i-1]) & 1) res = min(res, i);
        }
        reverse(a.begin(), a.end());
        for(int i = 1; i < n; i++) {
            if((a[i] - a[i-1]) & 1) res = min(res, i);
        }
        cout << res << '\n';
    } else {
        cout << "0\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}