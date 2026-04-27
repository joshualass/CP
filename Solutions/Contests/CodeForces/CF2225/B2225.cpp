#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    string s; cin >> s;
    int cnt = 0;
    for(int i = 1; i < sz(s); i++) {
        if(s[i] == s[i-1]) cnt++;
    }

    cout << (cnt <= 2 ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}