#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int ok = 1;
    for(int i = 0; i < n; i++) {
        int d = min(i, n - i - 1);
        if(n * 2 - 1 - d * 2 > a[i]) ok = 0;
    }
    cout << (ok ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}