#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    string s; cin >> s;
    ll res = 0;
    ll lo = -1;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '0') {
            if(lo != -1) {
                res += i - lo + 1;
                lo++;
            }
        } else {
            if(lo == -1) {
                lo = i;
            }
        }
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}