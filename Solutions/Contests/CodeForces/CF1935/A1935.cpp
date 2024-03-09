#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    string rev = s;
    reverse(rev.begin(), rev.end());
    if(rev < s) {
        if(n & 1) {
            cout << rev << '\n';
        } else {
            cout << rev << s << '\n';
        }
    } else {
        if(n & 1) {
            cout << s << rev << '\n';
        } else {
            cout << s << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}