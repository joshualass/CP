#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, p, l, e, r, s, n; cin >> n;

    while(!cin.eof()) {
        cin >> p >> l >> e >> r >> s >> n;

        for(int i = 0; i < n; i++) {
            int next_l = m * e;
            int next_p = l / r;
            int next_m = p / s;
            l = next_l, p = next_p, m = next_m;
        }

        cout << m << '\n';

        cin >> m;
    }

    return 0;
}