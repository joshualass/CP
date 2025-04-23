#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    s.insert(s.begin(), '0');
    int d = 0;
    for(int i = 1; i < s.size(); i++) {
        if(s[i-1] != s[i]) d++;
    }
    cout << n + d - max(0, min(2, d - 1)) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}