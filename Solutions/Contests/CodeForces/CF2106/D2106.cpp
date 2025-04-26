#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    vector<int> pre(n), suf(n);
    for(int i = 0; i < n; i++) {
        int prev = (i ? pre[i-1] : -1);
        if(prev != m - 1) {
            if(a[i] >= b[prev+1]) {
                prev++;
            }
        }
        pre[i] = prev;
    }
    for(int i = n - 1; i >= 0; i--) {
        int prev = (i == n - 1 ? m : suf[i+1]);
        if(prev) {
            if(a[i] >= b[prev - 1]) {
                prev--;
            }
        } 
        suf[i] = prev;
    }
    int res = INT_MAX;
    if(pre.back() == m - 1) res = 0;

    if(suf[0] == 1) res = min(res, b[0]);
    if(pre[n-1] == m - 2) res = min(res, b[m-1]);

    for(int i = 1; i < n; i++) {
        int p = pre[i-1], s = suf[i];
        if(p + 2 >= s) {
            res = min(res, b[min(m-1,p+1)]);
        }
    }
    cout << (res == INT_MAX ? -1 : res) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}