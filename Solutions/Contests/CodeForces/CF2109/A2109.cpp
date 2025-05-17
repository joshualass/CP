#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    int prev = 1;
    int ok = 1, s = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(prev == 0 && x == 0) ok = 0;
        s += x;
        prev = x;
    }
    if(s == n) ok = 0;
    cout << (!ok ? "YES" : "NO") << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}