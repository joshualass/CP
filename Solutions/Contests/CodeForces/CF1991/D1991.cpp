#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    if(n < 6) {
        vector<int> bruh = {1, 2, 2, 3, 3};
        if(n == 1) {
            cout << "1\n";
        } else if(n <= 3) {
            cout << "2\n";
        } else {
            cout << "3\n";
        }
        for(int i = 0; i < n; i++) {
            cout << bruh[i] << " \n"[i == n - 1];
        }
    } else {
        cout << "4\n";
        for(int i = 0; i < n; i++) {
            cout << i % 4 + 1 << " \n"[i == n - 1];
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