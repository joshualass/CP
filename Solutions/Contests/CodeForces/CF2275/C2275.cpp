#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> a(2);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i & 1].push_back(x);
    }

    ll res = 0;
    map<int,int> m;

    auto process = [&](vector<int> b) -> void {
        for(int i = 0; i < sz(b); i++) {
            if(i + 2 < sz(b)) {
                res += m[b[i] + b[i + 1] - b[i + 2]];
            }
            if(i >= 2) {
                m[b[i - 2] + b[i - 1] - b[i]]++;
            }
        }
    };

    for(int i = 0; i < 2; i++) process(a[i]);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}