#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    ll res = 0;
    for(int i = 0; i < n; i++) {
        res += max(a[i] - a[0], a[n-1] - a[i]);
    
    }
    cout << res - (a[n-1] - a[0]) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}