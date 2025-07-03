#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    string s; cin >> s;

    for(int i = 0; i < s.size(); i++) {
        for(int j = '9'; j >= '0'; j--) {
            if(s[i] != j) {
                cout << ((char) j);
            }
        }
        for(int j = '9'; j >= '0'; j--) {
            if(s[i] != j) {
                cout << ((char) j);
            }
        }
        if(i + 1 != s.size()) cout << s[i];
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}