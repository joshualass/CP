#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, x; cin >> n >> x;
    for(int i = 0; i < x; i++) cout << i << " ";
    for(int i = x; i < n; i++) {
        cout << n - 1 - (i - x) << " ";
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