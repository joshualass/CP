#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, strats, b, m; cin >> n >> strats >> b >> m;
    string s; cin >> s;

    int best = -1;
    ll best_money = LLONG_MIN;
    for(int i = 0; i < strats; i++) {
        ll bal = b;
        for(int j = 0; j < n; j++) {
            char c;
            ll coin;
            cin >> c >> coin;
            if(bal - coin < m) continue;
            if(c == s[j]) {
                bal += coin;
            } else {
                bal -= coin;
            }
        }
        if(bal > best_money) {
            best = i;
            best_money = bal;
        }
    }

    cout << best + 1 << " " << best_money << '\n';

    return 0;
}
