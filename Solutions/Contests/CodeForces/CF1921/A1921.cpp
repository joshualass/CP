#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    vector<pair<int,int>> v(4);
    for(auto &p : v) cin >> p.first >> p.second;
    sort(v.begin(),v.end());
    cout << (v.back().first - v.front().first) * (v.back().second - v.front().second) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}