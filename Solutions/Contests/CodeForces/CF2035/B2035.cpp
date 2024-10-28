#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    if(n & 1) {
        if(n <= 3) {
            cout << "-1\n";
        } else {
            for(int i = 0; i < n - 4; i++) {
                cout << '3';
            }
            cout << "6366\n";
        }
    } else {
        for(int i = 0; i < n - 2; i++) {
            cout << '3';
        }
        cout << "66\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}