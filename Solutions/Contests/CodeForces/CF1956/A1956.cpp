#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int k, q; cin >> k >> q;
    int lo = INT_MAX;
    for(int i = 0; i < k; i++) {
        int n; cin >> n;
        lo = min(lo,n);
    }
    for(int i = 0; i < q; i++) {
        int n; cin >> n;
        cout << min(n,lo-1) << " \n"[i == q - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}