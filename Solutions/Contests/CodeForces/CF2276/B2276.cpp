#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    string s; cin >> s;
    int a = 0, b = 1, c = 0;
    for(int i = 2; i < sz(s); i++) {
        if(s[i-2] == s[i-1] && s[i-1] == s[i]) a = 1;
        if(s[i-2] != s[i]) b = 1;
        if(s[i-2] == s[i] && s[i-2] != s[i-1]) c = 1;
    }

    cout << a + b + c << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}