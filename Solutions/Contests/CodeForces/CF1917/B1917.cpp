#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    string str; cin >> str;
    ll ans = 0;
    vector<bool> visited(26);
    for(int i = 0; i < n; i++) {
        if(!visited[str[i] - 'a']) {
            ans += n - i;
            visited[str[i] - 'a'] = 1;
        }
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