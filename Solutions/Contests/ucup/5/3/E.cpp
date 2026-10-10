#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int maxn = 1e6;
ll pc[maxn + 1];

void solve() {
    
    ll l, r; cin >> l >> r;

    if(r <= 1000) {
        for(int i = l; i < r; i++) {
            for(int j = i + 1; j <= r; j++) {
                if(pc[i] == pc[j]) {
                    cout << i << " " << j << '\n';
                    return;
                }
            }
        }
    } else {
        ll x = l / 2;
        while(x * 2 < l || (x % 2 == 1) || (x % 3 == 0)) x++;
        assert(x * 3 <= r);
        cout << x * 2 << " " << x * 3 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 1; i <= maxn; i++) pc[i] = i;
    
    for(int i = 1; i <= maxn; i++) {
        for(int j = 2; i * j <= maxn; j++) {
            pc[i * j] -= pc[i];
        }
    }

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}