#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    if(n == 4) {
        cout << "2025\n";
    } else if(n == 5) {
        cout << "42025\n";
    } else if(n == 6) {
        cout << "224955\n";
    } else {
        if(n & 1) {
            cout << "1" << string((n - 7) / 2, '0') << "205\n";
        } else {
            cout << "4" << string((n - 8) / 2, '0') << "205\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int casi; cin >> casi;
    // while(casi-->0) solve();

    for(ll i = 0; i <= 1000; i++) {
        ll num = i * i;
        string s = to_string(num);
        if(s.size() == 6 && num % 10000 == 2025) {
            cout << "i : " << i << '\n';
        }
    }

    return 0;
}