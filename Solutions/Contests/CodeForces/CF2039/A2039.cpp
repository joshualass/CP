#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    // for(int i = 2; i <= n+1; i++) {
    //     cout << i << " \n"[i == n + 1];
    // }
    for(int i = 0; i < n; i++) {
        cout << i * 2 + 1 << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}