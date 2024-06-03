#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    if((count(s.begin(), s.end(), '0') & 1) || (count(s.begin(), s.end(), '1') & 1)) {
        cout << "-1\n";
        return;
    }
    bool p = 0;
    vector<int> swaps;
    for(int i = 0; i < n * 2; i += 2) {
        if(s[i] != s[i+1]) {
            swaps.push_back(i + (s[i] == ('0' + p)));
            p = abs(p - 1); //don't use ^= :)
        }
    }
    cout << swaps.size() << " ";
    for(int i = 0; i < swaps.size(); i++) {
        cout << swaps[i] + 1 << " "[i == swaps.size() - 1];
    }
    cout << '\n';
    for(int i = 0; i < n * 2; i += 2) {
        cout << i + 1 << " \n"[i == n * 2 - 2];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}