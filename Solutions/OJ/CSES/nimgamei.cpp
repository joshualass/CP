#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    int g = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        g ^= x;
    }
    cout << (g ? "first" : "second") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}