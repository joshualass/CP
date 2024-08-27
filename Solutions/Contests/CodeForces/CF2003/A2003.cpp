#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    set<char> ss;
    for(char c : s) {
        ss.insert(c);
    }
    if(ss.size() > 1 && s.front() != s.back()) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}