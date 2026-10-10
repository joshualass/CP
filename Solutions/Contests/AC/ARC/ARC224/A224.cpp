#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll k; cin >> k;
    ll t = k;
    while(1) {
        if(to_string(t).find("00") != string::npos) {
            cout << t << '\n';
            return;
        }
        t += k;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}