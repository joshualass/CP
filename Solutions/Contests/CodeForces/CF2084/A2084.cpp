#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    if(n & 1) {
        for(int i = 0; i < n; i++) {
            cout << (i == 0 ? n : i) << " \n"[i == n - 1];
        }
    } else {
        cout << "-1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}