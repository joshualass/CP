#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<int,2>> res;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        for(int j = 1; j <= n; j++) {
            if(x != j) res.push_back({i, j});
        }
    }

    cout << "1\n";
    cout << n << " " << res.size() << '\n';
    for(auto x : res) cout << x[0] << " " << x[1] << '\n';

    return 0;
}
