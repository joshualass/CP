#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, m, k; cin >> n >> m >> k;

    if((n + m) % 2 == k % 2 && k >= (n + m - 2)) {
        cout << "YES\n";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m - 1; j++) {
                if(i == n - 1) {
                    cout << ((i + j) % 2 == 0 ? "R " : "B ");
                } else {
                    cout << "R ";
                }
            }
            cout << '\n';
        }
        for(int i = 0; i < n - 1; i++) {
            for(int j = 0; j < m; j++) {
                if(j == 0) {
                    cout << ((i + j) % 2 == 0 ? "R " : "B ");
                } else {
                    cout << "B ";
                }
            }
            cout << '\n';
        }
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}