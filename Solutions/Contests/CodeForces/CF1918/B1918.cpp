#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(auto &x : v) cin >> x.first;
    for(auto &x : v) cin >> x.second;
    sort(v.begin(), v.end(), [] (const pair<int,int> &lhs, const pair<int,int> &rhs) -> bool {
        return lhs.first + lhs.second < rhs.first + rhs.second;
    });
    for(int i = 0; i < n; i++) {
        cout << v[i].first << " \n"[i == n - 1];
    }
    for(int i = 0; i < n; i++) {
        cout << v[i].second << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}