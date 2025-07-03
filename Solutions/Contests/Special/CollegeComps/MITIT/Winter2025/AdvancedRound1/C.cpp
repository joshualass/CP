#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    map<int,int> m;
    vector<vector<int>> liss;
    for(int i = n - 1; i >= 0; i--) {
        if(m.lower_bound(a[i]) != m.begin()) {
            auto [prev_val, lis_idx] = *--m.lower_bound(a[i]);
            liss[lis_idx].push_back(i);
            m.erase(prev_val);
            m[a[i]] = lis_idx;
        } else {
            int lis_idx = liss.size();
            liss.push_back({i});
            m[a[i]] = lis_idx;
        }
    }
    vector<int> res;

    sort(liss.begin(), liss.end(), [&](const auto &lhs, const auto &rhs) {
        return lhs.size() > rhs.size();
    });

    for(int i = 0; i < min((int) liss.size(), (k + 1) / 2); i++) {
        for(int x : liss[i]) res.push_back(x);
    }

    if(res.size() >= k) {
        cout << "YES\n";
        sort(res.begin(), res.begin() + k);
        for(int i = 0; i < k; i++) {
            cout << res[i] + 1 << " \n"[i == k - 1];
        }
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}