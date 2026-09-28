#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    
    int asum = accumulate(a.begin(), a.end(), 0);
    int bsum = accumulate(b.begin(), b.end(), 0);

    if(asum != bsum) {
        cout << "No\n";
        return;
    }

    if(asum != 1) {
        cout << "Yes\n";
        return;
    }

    int f = -1, s = -1;
    for(int i = 0; i < n; i++) {
        if(a[i]) f = i;
        if(b[i]) s = i;
    }

    int ok = (f == 0 && s == 0 || f == n - 1 && s == n - 1 || 0 < f && f < n - 1 && 0 < s && s < n - 1);

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}