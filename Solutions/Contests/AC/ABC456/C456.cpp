#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;

    int l = 0;

    ll res = 0;
    auto addt = [&](int len) -> void {
        res += 1LL * len * (len + 1) / 2;
    };

    for(int i = 1; i < sz(s); i++) {
        if(s[i] == s[i-1]) {
            addt(i - l); 
            l = i;
        }
    }

    addt(sz(s) - l);

    cout << res % 998244353 << '\n';

    return 0;
}
