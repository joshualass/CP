#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> t0(n);
    iota(t0.begin(), t0.end(), 1);
    if(a == t0) {
        cout << "0\n";
        return;
    }

    int found1 = 0;

    int lo = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] == i + 1 && lo <= i) {
            found1 = 1;
        }
        lo = max(lo, a[i]);
    }
    if(found1) {
        cout << 1 << '\n';
        return;
    }

    if(n >= 3 && a[0] == n && a[n-1] == 1) {
        cout << "3\n";
    } else {
        cout << "2\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}