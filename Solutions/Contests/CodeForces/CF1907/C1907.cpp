#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    string str; cin >> str;
    vector<int> cnts(26);
    for(int i = 0; i < n; i++) {
        cnts[str[i] - 'a']++;
    }
    int most = *max_element(cnts.begin(), cnts.end());
    int nonmost = n - most;
    int mostremove = min(nonmost*2, n / 2 * 2);
    cout << n - mostremove << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}