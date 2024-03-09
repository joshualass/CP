#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    set<int> s(v.begin(), v.end());
    vector<int> v1(s.begin(), s.end());
    int loidx = 0;
    int ans = 0;
    for(int i = 0; i < v1.size(); i++) {
        while(v1[i] - v1[loidx] >= n) loidx++;
        ans = max(ans,i-loidx+1);
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}