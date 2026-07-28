#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    
    for(int f = 2; f * f <= n; f++) {
        if(n % f == 0) {
            cout << n / f << " " << n - n / f << '\n';
            return;
        }
    }

    cout << 1 << " " << n - 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}