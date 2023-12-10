#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<pair<ll,ll>> v(n);

    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        v[i] = {num,i};
    }
    sort(v.begin(), v.end());

    int loidx = 0;
    ll sum = v[0].first;
    vector<int> ans(n);

    for(int i = 1; i < n; i++) {
        if(sum < v[i].first) {
            while(loidx != i) {
                ans[v[loidx++].second] = i - 1;
            }
        }
        sum += v[i].first;
    }
    while(loidx != n) {
        ans[v[loidx++].second] = n - 1;
    }
    for(auto x : ans) cout << x << " ";
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}