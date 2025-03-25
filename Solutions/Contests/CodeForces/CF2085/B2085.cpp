#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<array<int,2>> res;
    if(count(a.begin() + 2, a.end(), 0)) {
        a = {a[0], a[1], 1};
        res.push_back({2, n});
    }
    if(count(a.begin(), a.begin() + 2, 0)) {
        a.erase(a.begin());
        a[0] = 1;
        res.push_back({0,2});
    }
    res.push_back({0, (int)  a.size()});
    cout << res.size() << '\n';
    for(auto op : res) {
        cout << op[0] + 1 << " " << op[1] << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}