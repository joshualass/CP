#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int ok = n % 2 == 0;
    int lo = INT_MAX, hi = 0;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            lo = min(lo, a[i]);
        } else {
            hi = max(hi, a[i]);
        }
    }

    cout << (ok && hi + 1 < lo ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}