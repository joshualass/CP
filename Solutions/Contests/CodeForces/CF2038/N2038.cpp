#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    string s; cin >> s;

    if(s[0] > s[2]) {
        s[1] = '>';
    } else if(s[0] < s[2]) {
        s[1] = '<';
    } else {
        s[1] = '=';
    }

    cout << s << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}