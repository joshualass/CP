#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    int res = 1;
    for(int i = 1; i < n; i++) {
        if(s[i] != s[i-1]) {
            res++;
        }
    }

    int sub = 0;
    for(int i = 1; i + 1 < n; i++) {
        if(s[i] != s[i-1] && s[i] != s[i+1]) {
            sub = max(sub, 1);
            if(s[i-1] == s[i+1]) sub = 2;
        }
    }

    cout << res - sub << '\n';

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