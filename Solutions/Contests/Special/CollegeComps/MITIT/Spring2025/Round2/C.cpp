#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

set<char> stt = {'y', 'g', 'b', 'r'};

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    string res = "";
    for(int i = 2; i < n; i++) {
        set<char> t = stt;
        for(int j = i - 2; j <= i; j++) t.erase(s[j]);
        res.push_back(*t.begin());
    }
    res.push_back('y');
    res.push_back('y');

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}