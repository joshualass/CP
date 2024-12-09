#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    string s; cin >> s;
    int c = 0;
    int op = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            c++;
        } else {
            c = 0;
        }
        if(c == m) {
            op++;
            i += k - 1;
            c = 0;
        }
    }
    cout << op << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}