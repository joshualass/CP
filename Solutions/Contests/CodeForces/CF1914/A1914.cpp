#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    string str; cin >> str;
    vector<int> cnts(26);

    int ans = 0;
    for(int i = 0; i < n; i++) {
        cnts[str[i] - 'A']++;
        if(cnts[str[i] - 'A'] == str[i] - 'A' + 1) ans++;
    }
    cout << ans << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}