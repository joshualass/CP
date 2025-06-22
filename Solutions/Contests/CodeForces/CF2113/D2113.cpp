#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    int l = 0, r = n;
    while(l != r) {
        int m = (l + r + 1) / 2;
        int win = m, loss = n - m;

        int dealer_lo = INT_MAX;
        for(int i = 0; i < loss + 1; i++) dealer_lo = min(dealer_lo, b[i]);

        int player_lo_idx = 0;
        for(int i = 1; i < win; i++) {
            if(a[i] < a[player_lo_idx]) player_lo_idx = i;
        }

        int player_hi_idx = win;

        for(int i = win + 1; i < n; i++) {
            if(a[i] > a[player_hi_idx]) player_hi_idx = i;
        }

        int ds = 0;

        if(player_hi_idx < n && a[player_lo_idx] < a[player_hi_idx]) {
            ds = 1;
            swap(a[player_lo_idx], a[player_hi_idx]);
        }

        int ok = 1;
        for(int i = 0; i < win; i++) {
            if(a[i] < dealer_lo) ok = 0;
        }

        if(ds) {
            swap(a[player_lo_idx], a[player_hi_idx]);
        }

        if(ok) {
            l = m;
        } else {
            r = m - 1;
        }

    }

    cout << l << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}