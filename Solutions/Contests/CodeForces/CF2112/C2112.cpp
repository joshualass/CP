#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    ll res = 0;
    auto add_cnt = [&](int a, int b, int lo, int hi) -> void {
        // cout << "a : " << a << " b : " << b << " lo : " << lo << " hi : " << hi << '\n';
        lo = max(lo, b + 1);
        // cout << "max things\n";
        // cout << "a : " << a << " b : " << b << " lo : " << lo << " hi : " << hi << '\n';
        int len = max(0, hi - lo - ((int) a >= lo && a < hi) - ((int) b >= lo && b < hi));
        res += len;
    };

    for(int i = 0; i < n; i++) {
        int lo = 0, hi = n;
        for(int j = n - 1; j > i; j--) {
            while(lo < n && a[i] + a[j] + a[lo] <= a[n-1]) lo++;
            while(hi && a[i] + a[j] <= a[hi - 1]) hi--;
            add_cnt(i, j, lo, hi);
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