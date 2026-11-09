#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int res = 0;
    
    for(int bit = 29; bit >= 0; bit--) {
        int cnt = 0;
        for(int x : a) {
            cnt += (x >> bit) & 1;
        }
        if(cnt) {
            res += 1 << bit;
            if(cnt != n) {
                res += (1 << bit) - 1;
                break;
            }
        }
    }

    cout << res << '\n';

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