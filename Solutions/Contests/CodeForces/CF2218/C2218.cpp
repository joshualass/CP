#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        cout << i + 1 << " " << 3 * n - i * 2 - 1 << " " << 3 * n - i * 2 << " ";
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