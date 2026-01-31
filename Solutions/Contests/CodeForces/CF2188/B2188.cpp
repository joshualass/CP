#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    
    int res = 0;
    int len = 1;
    for(char c : s) {
        if(c == '0') {
            len++;
        } else {
            res++;
            res += len / 3;
            len = 0;
        }
    }
    len++;
    res += len / 3;
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}