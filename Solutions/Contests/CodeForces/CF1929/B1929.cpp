#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k; cin >> n >> k;
    int maxtwo = n * 2 - 2;
    if(k > maxtwo * 2) {
        cout << maxtwo + k - maxtwo * 2 << '\n';
    } else {
        cout << (k + 1) / 2 << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}