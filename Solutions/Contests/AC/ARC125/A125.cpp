#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> s(n), t(m);
    for(int &x : s) cin >> x;
    for(int &x : t) cin >> x;
    if(count(t.begin(), t.end(), 0) && (count(s.begin(), s.end(),0) == 0) || count(t.begin(), t.end(), 1) && (count(s.begin(), s.end(),1) == 0)) {
        cout << "-1\n";
        return 0;
    }

    int ops = m;

    int nearesttoggle = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] != s[0] || s[(n - i) % n] != s[0]) {
            break;
        }
        nearesttoggle++;
    }
    int cur = s[0];
    for(int i = 0; i < m; i++) {
        if(t[i] != cur) {
            ops += nearesttoggle;
            nearesttoggle = 1;
            cur ^= 1;
        }
    }

    cout << ops << '\n';

    return 0;
}