#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, q; cin >> n >> q;
    for(int i = 1; i < n; i++) {
        cout << i << " " << i + 1 << '\n';
    }

    int cur = n - 1;

    for(int qq = 0; qq < q; qq++) {
        int d; cin >> d;
        if(d == cur) {
            cout << "-1 -1 -1\n";
        } else {
            cout << n << " " << cur << " " << d << '\n';
            cur = d;
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}