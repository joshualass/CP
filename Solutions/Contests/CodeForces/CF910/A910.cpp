#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;
    string str; cin >> str;
    int bcnt = 0;
    for(int i = 0; i < n; i++) {
        if(str[i] == 'B') bcnt++;
    }
    if(bcnt == k) {
        cout << "0\n";
    } else {
        cout << "1\n";
        if(bcnt > k) {
            int idx = 0;
            while(idx < n) {
                if(str[idx] == 'B') {
                    bcnt--;
                }
                if(bcnt == k) break;
                idx++;
            }
            cout << idx + 1 << " A\n";
        } else {
            int idx = 0;
            while(idx < n) {
                if(str[idx] == 'A') {
                    bcnt++;
                }
                if(bcnt == k) break;
                idx++;
            }
            cout << idx + 1 << " B\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}