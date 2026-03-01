#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    int f = 0, res = 1;
    for(int i = 1; i < n; i++) {
        if(s[i] == s[i-1]) {
            f = 1;
        } else {
            res++;
        }
    }
    if(s.front() == s.back()) f = 0;
    cout << res + f << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}