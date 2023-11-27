#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    string str; cin >> str;

    int cnt = 0;
    int curr = 0;
    int most = 0;

    for(int i = 0; i < n; i++) {
        if(str[i] == '#') {
            curr = 0;
        }
        if(str[i] == '.') {
            cnt++;
            curr++;
            most = max(most,curr);
        }
    }
    if(most >= 3) {
        cout << "2\n";
    } else {
        cout << cnt << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}