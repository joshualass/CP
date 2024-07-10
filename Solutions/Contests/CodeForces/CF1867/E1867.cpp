#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;


// ask [l,r) 0-indexed
int ask(int l, int r) {
    cout << "? " << l + 1 << endl;
    int ans; cin >> ans;
    return ans;
}

void solve() {
    int n, k; cin >> n >> k;

    int res = 0;
    while(n - k >= k) {
        res ^= ask(n-k,n);
        n -= k;
    }

    int d = n - k;
    int d2 = d / 2;
    
    res ^= ask(0,k);
    ask(0,k);
    res ^= ask(d2,k+d2);
    res ^= ask(d,n);

    cout << "! " << res << endl;
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}