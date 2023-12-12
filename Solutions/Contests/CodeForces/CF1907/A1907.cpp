#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    string str; cin >> str;
    for(int i = 'a'; i <= 'h'; i++) {
        if(i != str[0]) {
            cout << (char)i << str[1] << '\n';
        }
    }
    for(int i = '1'; i <= '8'; i++) {
        if(i != str[1]) {
            cout << str[0] << (char)i << '\n';
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