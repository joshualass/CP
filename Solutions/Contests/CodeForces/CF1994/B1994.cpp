#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s, t; cin >> s >> t;
    int sp = INT_MAX - 1;
    int tp = INT_MAX;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            sp = i;
            break;
        }
    }
    for(int i = 0; i < n; i++) {
        if(t[i] == '1') {
            tp = i;
            break;
        }
    }
    cout << (sp <= tp ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}