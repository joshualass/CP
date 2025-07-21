#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, k; cin >> n >> k;
    k--;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int st = a[k];

    sort(a.begin(), a.end());
    int maxdiff = 0;
    for(int i = 1; i < n; i++) {
        maxdiff = max(maxdiff, a[i] - a[i-1]);
    }

    cout << (st >= maxdiff ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}