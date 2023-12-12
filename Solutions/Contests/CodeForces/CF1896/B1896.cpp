#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    string str; cin >> str;

    int aidx = -1;
    int bidx = -1;

    for(int i = 0; i < n; i++) {
        if(aidx == -1 && str[i] == 'A') {
            aidx = i;
        }
        if(str[i] == 'B') {
            bidx = i;
        }
    }
    if(bidx > aidx && aidx != -1 && bidx != -1) {
        cout << bidx - aidx << '\n';
    } else {
        cout << "0\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}