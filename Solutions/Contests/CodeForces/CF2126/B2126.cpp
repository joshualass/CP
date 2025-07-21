#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, k; cin >> n >> k;
    int res = 0;
    int p = -1;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x == 1) {
            int len = i - p;
            res += len / (k + 1);
            p = i;
        }
    }    
    int len = n - p;
    res += len / (k + 1);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}