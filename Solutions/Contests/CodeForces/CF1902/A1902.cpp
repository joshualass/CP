#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    string str; cin >> str;
    int zerocnt = 0;
    int onecnt = 0;
    for(int i = 0; i < n; i++) {
        if(str[i] == '0') {
            zerocnt++;
        } else {
            onecnt++;
        }
    }
    if(zerocnt > 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}