#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x]++;
    }
    vector<pair<int,int>> a(m.begin(), m.end());
    sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) -> bool {
        return lhs.second < rhs.second;
    });
    int res = 0;
    for(int i = 0; i < a.size(); i++) {
        int t = min(a[i].second, k);
        a[i].second -= t;
        k -= t;
        if(a[i].second) res++;
    }
    cout << max(res, 1) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}