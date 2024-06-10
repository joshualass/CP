#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll num; cin >> num;
    vector<int> digs;
    while(num) {
        digs.push_back(num % 10);
        num /= 10;
    }
    bool ok = 1;
    for(int i = 0; i < digs.size(); i++) {
        if(i == 0) {
            if(digs[i] == 9) ok = 0;
        } else if(i == digs.size() - 1) {
            if(digs[i] != 1) ok = 0;
        } else {
            if(digs[i] == 0) ok = 0;
        }
    }
    cout << (ok ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}