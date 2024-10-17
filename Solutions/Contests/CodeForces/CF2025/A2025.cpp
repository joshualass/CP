#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    string s1, s2; cin >> s1 >> s2;
    int samecnt = 0;
    for(int i = 0; i < min(s1.size(), s2.size()); i++) {
        if(s1[i] == s2[i]) samecnt++;
        else break;
    }
    cout << min((int) s1.size() + s2.size(), (int) s1.size() + s2.size() + 1 - samecnt) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}