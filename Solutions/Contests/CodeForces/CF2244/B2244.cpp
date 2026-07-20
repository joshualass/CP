#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    int ok = 1;
    ll sum = 0, need = 0;
    for(int i = 1; i <= n; i++) {
        need += i;
        int x; cin >> x;
        sum += x;
        if(sum < need) ok = 0;
    }

    cout << (ok ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}