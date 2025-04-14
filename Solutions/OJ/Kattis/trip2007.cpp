#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    while(n) {

        multiset<int> ms;
        for(int i = 0; i < n; i++) {
            int x; cin >> x;
            ms.insert(x);
        }

        vector<vector<int>> ans;

        while(ms.size()) {
            int p = 1e9;
            vector<int> b;
            while(ms.lower_bound(p) != ms.begin()) {
                int nx = *--ms.lower_bound(p);
                ms.erase(ms.find(nx));
                b.push_back(nx);
                p = nx;
            }
            ans.push_back(b);
        }

        cout << ans.size() << '\n';
        for(auto b : ans) {
            for(auto c : b) cout << c << " ";
            cout << '\n';
        }

        cin >> n;
    }

    return 0;
}
