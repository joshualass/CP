#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    bool ok = 1;
    for(int i = 0; i < n - 1; i++) {
        bool loisdig = s[i] >= '0' && s[i] <= '9';
        bool hiisdig = s[i+1] >= '0' && s[i+1] <= '9';
        if(loisdig && !hiisdig) {
        } else if(!loisdig && hiisdig) {
            ok = 0;
        } else {
            ok &= s[i] <= s[i+1];
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