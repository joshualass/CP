#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> pre(n), suf(n);
    int c = 0;
    int ep = n, ls = -1;
    for(int i = 0; i < n; i++) {
        c += (a[i] <= k ? 1 : -1);
        if(c >= 0) {
            pre[i] = 1;
            ep = min(ep, i);
        }
    }
    c = 0;
    for(int i = n - 1; i >= 0; i--) {
        c += (a[i] <= k ? 1 : -1);
        if(c >= 0) {
            suf[i] = 1;
            ls = max(ls, i);    
        }
    }
    int ok = ep + 1 < ls;

    c = 0;
    for(int i = 1; i < n - 1; i++) {
        c += (a[i] <= k ? 1 : -1);
        if(a[i] <= k) c = max(c, 1);
        if(c >= 0 && suf[i+1]) ok = 1;
    }
    c = 0;
    for(int i = n - 2; i > 0; i--) {
        c += (a[i] <= k ? 1 : -1);
        if(a[i] <= k) c = max(c, 1);
        if(c >= 0 && pre[i-1]) ok = 1;
    }

    cout << (ok ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}