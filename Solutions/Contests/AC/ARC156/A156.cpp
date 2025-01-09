#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    if((count(s.begin(), s.end(), '1') & 1) || n == 3 && s[0] != s[2]) {
        cout << "-1\n";
        return;
    }
    int ops = count(s.begin(), s.end(), '1') / 2;
    if(count(s.begin(), s.end(), '1') == 2 && s.find("11") != string::npos) {
        ops++;
    }
    if(s == "0110") ops++;
    cout << ops << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}