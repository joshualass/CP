#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    string pre = "", suf = "";
    while(s.size() && s.back() == '1') {
        suf.push_back(s.back());
        s.pop_back();
    }

    reverse(s.begin(),s.end());

    while(s.size() && s.back() == '0') {
        pre.push_back(s.back());
        s.pop_back();
    }

    reverse(s.begin(),s.end());

    cout << pre + (s.size() ? "0" : "") + suf << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}