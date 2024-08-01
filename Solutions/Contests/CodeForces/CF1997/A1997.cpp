#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    string s; cin >> s;

    for(int i = 0; i < s.size() - 1; i++) {
        if(s[i] == s[i+1]) {
            cout << s.substr(0,i + 1) << (char) (((s[i] - 'a' + 1) % 26) + 'a') << s.substr(i + 1) << '\n';
            return;
        }
    }
    cout << s << (char) (((s.back() - 'a' + 1) % 26) + 'a') << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}