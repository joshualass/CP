#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;

    for(int i = 0; i < n; i++) {
        if(i < k) {
            cout << i + 1 << " ";
        } else {
            cout << n + k - i << " ";
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