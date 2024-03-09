#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int lo = -1;
    int hi = -2;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'B') {
            lo = min(lo == -1 ? INT_MAX : lo,i);
            hi = max(hi,i);
        }
    }
    cout << hi - lo + 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}