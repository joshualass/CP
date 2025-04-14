#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    int sc = m + 1;
    int scl = max(k,n / sc);
    
    int c = 0;
    for(int i = 0; i < n; i++) {
        if(c == scl) {
            c = 0;
        }
        cout << c++ << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}