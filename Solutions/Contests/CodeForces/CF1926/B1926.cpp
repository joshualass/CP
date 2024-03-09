#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    set<int> s;
    s.insert(0);
    for(int i = 0; i < n; i++) {
        string str; cin >> str;
        s.insert(count(str.begin(),str.end(),'1'));
    }
    cout << (s.size() == 2 ? "SQUARE" : "TRIANGLE") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}