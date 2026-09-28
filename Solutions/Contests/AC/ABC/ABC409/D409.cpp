#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    int l = n - 1, r = n;
    for(int i = 0; i < n - 1; i++) {
        if(s[i] > s[i+1]) {
            l = i;
            break;    
        }
    }
    for(int i = l; i < n; i++) {
        if(s[l] < s[i]) {
            r = i;
            break;
        }
    }

    // cout << l << " " << r << '\n';

    s.insert(s.begin() + r, s[l]);
    s.erase(s.begin() + l);
    
    cout << s << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}