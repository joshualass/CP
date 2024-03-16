#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    if(n & 1) {
        cout << "no\n";
        return;
    }
    cout << "yes\n";
    for(int i = 0; i < n / 2; i++) {
        if(i & 1) {
            cout << "AA";
        } else {
            cout << "BB";
        }
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}