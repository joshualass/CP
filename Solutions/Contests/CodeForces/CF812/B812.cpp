#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    int stop = n;
    for(int i = n - 1; i >= 0; i--) {
        if(a[i].find('1') != string::npos) {
            stop = i;
        }
    }

    int pl = -1, pr = 1e9;
    for(int i = n - 1; i >= stop; i--) {
        int hi = 0, lo = m + 1;
        for(int j = 0; j < m + 2; j++) {
            if(a[i][j] == '1') {
                hi = j;
                lo = min(lo, j);
            }
        }
        int nl, nr;
        if(i == stop) {
            nl = 1 + hi + pl;
            nr = 1 + (m + 1 - lo) + pr;
        } else {
            nl = min(1 + pl + hi * 2, pr + m + 2);
            nr = min(1 + pr + (m + 1 - lo) * 2, pl + m + 2);
        }
        pl = nl;
        pr = nr;
    }

    cout << max(0,min(pl,pr)) << '\n';

    return 0;
}