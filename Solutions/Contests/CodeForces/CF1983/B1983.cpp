#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> ar(n), ac(m), br(n), bc(m);
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            int num = s[j] - '0';
            ar[i] += num;
            ac[j] += num;
        }
    }
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            int num = s[j] - '0';
            br[i] += num;
            bc[j] += num;
        }
    }
    bool ok = 1;
    for(int i = 0; i < n; i++) {
        if(ar[i] % 3 != br[i] % 3) ok = 0;
    }
    for(int i = 0; i < m; i++) {
        if(ac[i] % 3 != bc[i] % 3) ok = 0;
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