#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int x, a, b, c; cin >> x >> a >> b >> c;
    int cnt = 0;
    while(x) {
        if(x == 1) {
            x = a;
        } else if(x == 2) {
            x = b;
        } else if(x == 3) {
            x = c;
        }
        cnt++;
    }
    cout << (cnt == 3 ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}