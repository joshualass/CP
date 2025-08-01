#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, x; cin >> n >> k >> x;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    vector<string> b;

    auto dfs = [&](auto self, int len, string cur) -> void {
        if(len == k) {
            b.push_back(cur);
            return;
        }
        for(int i = 0; i < n; i++) {
            self(self, len + 1, cur + a[i]);
        }
    };

    dfs(dfs, 0, "");

    sort(b.begin(), b.end());
    cout << b[x-1] << '\n';

    return 0;
}
