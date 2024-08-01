#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    ll res = 0;
    int open = 0;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            if(open) {
                open--;
                res += i;
            } else {
                open++;
                res -= i;
            }
        } else {
            if(s[i] == '(') {
                open++;
                res -= i;
            } else {
                open--;
                res += i;
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