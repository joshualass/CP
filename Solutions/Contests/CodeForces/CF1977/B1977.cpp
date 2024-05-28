#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(30);
    bool carry = 0;
    for(int i = 0; i < 30; i++) {
        if((n >> i) & 1) {
            if(carry == 0) {
                a[i] = -1;
                carry = 1;
            }
        } else {
            if(carry) {
                a[i] = 1;
                carry = 0;
            }
        }
    }

    for(int i = 0; i < 29; i++) {
        if(a[i] == -1 && a[i+1] == 1) {
            a[i] = 1;
            a[i+1] = 0;
        }
    }

    cout << a.size() << '\n';

    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << " \n"[i == a.size() - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}