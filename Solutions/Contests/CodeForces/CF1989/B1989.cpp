#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    string a, b; cin >> a >> b;
    int res = 0;
    for(int startb = 0; startb < b.size(); startb++) {
        int bptr = startb;
        for(int i = 0; i < a.size(); i++) {
            if(bptr < b.size() && a[i] == b[bptr]) bptr++;
        }
        res = max(res, bptr - startb);
    }
    cout << a.size() + b.size() - res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}