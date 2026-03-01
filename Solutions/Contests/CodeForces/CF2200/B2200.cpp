#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    int p; cin >> p;
    int f = 0;
    for(int i = 1; i < n; i++) {
        int x; cin >> x;
        if(x < p) f = 1;
        p = x;
    }

    cout << (f ? 1 : n) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}