#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s1, s2; cin >> s1 >> s2;
    string ans = "";
    ans.push_back(s1[0]);
    int late = n-1;
    int early = 0;
    bool stop = 0;
    for(int i = 1; i < n; i++) {
        if(s2[i-1] == '0' && s1[i] == '1' && !stop) {
            late = i - 1;
            stop = 1;
        }
        if(late == n-1) {
            ans.push_back(s1[i]);
        } else {
            ans.push_back(s2[i-1]);
        }
        if(s2[i-1] == '1' && s1[i] == '0' && !stop) {
            early = i;
        }
    }
    // cout << "early : " << early << " late : " << late << '\n';
    ans.push_back(s2.back());
    cout << ans << '\n';
    cout << late - early + 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}