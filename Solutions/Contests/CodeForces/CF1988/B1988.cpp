#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int one = 0;
    int zero = 0;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            if(s[i] == '0') {
                zero++;
            } else {
                one++;
            }
        } else {
            if(s[i] == '0') {
                if(s[i-1] != '0') {
                    zero++;
                }
            } else {
                one++;
            }
        }
    }
    cout << (one > zero ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}