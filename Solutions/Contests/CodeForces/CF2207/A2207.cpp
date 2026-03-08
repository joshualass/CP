#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    int sub = 0;
    for(int i = 1; i + 1 < n; i++) {
        if(s[i-1] == '1' && s[i] == '0' && s[i+1] == '1') {
            s[i] = '1';    
        }
    }
    int mx = count(s.begin(), s.end(), '1');
    for(int i = 1; i + 1 < n; i++) {
        if(s[i-1] == '1' && s[i] == '1' && s[i+1] == '1') {
            s[i] = '0';
            i++;
        }
    }

    int mn = count(s.begin(), s.end(), '1');
    cout << mn << " " << mx << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}