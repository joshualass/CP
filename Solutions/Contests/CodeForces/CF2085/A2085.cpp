#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    string rev(s);
    reverse(rev.begin(), rev.end());
    cout << (s < rev || k && count(s.begin(), s.end(), s[0]) != n ? "Yes" : "No") <<  '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}