#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    int c = count(s.begin(), s.end(), '1');
    if(c == 1) {
        cout << "0\n";
    } else if(c == 2) {
        cout << "1\n";
    } else {
        int lo = n, hi = -1;
        for(int i = 0; i < n; i++) {
            if(s[i] == '1') {
                lo = min(lo, i);
                hi = max(hi, i);
            }
        }
        cout << hi - lo << '\n';
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