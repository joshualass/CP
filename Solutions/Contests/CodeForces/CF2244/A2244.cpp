#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    int res = 0, cur = 0;
    for(char c : s) {
        if(c == '#') {
            cur++;
        } else {
            cur = 0;
        }
        res = max(res, cur);
    }
    cout << (res + 1) / 2 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}