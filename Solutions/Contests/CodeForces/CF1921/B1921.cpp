#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s1, s2; cin >> s1 >> s2;
    int a = 0, b = 0;
    for(int i = 0; i < n; i++) {
        if(s1[i] == '0' && s2[i] == '1') {
            a++;
        }
        if(s1[i] == '1' && s2[i] == '0') {
            b++;
        }
    }
    cout << max(a,b) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}