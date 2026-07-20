#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k, m; cin >> n >> k >> m;
    if(k > m) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for(int i = 0; i < n; i++) {
            if(i == 0) {
                cout << 1 + (m - k);
            } else {
                cout << 1;
            }
            cout << " \n"[i == n - 1];
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}