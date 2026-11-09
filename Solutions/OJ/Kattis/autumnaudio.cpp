#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    set<int> s;
    for(int i = 1; i < n; i++) {
        int test = a[i] - a[0];
        vector<int> vis(n);
        int ok = 1;
        int r = 0;
        for(int i = 0; i < n; i++) {
            if(vis[i] == 0) {
                vis[i] = 1;
                while(r < n && a[r] - a[i] < test || r < n && vis[r]) {
                    r++;
                }
                if(r < n && a[r] - a[i] == test) {
                    vis[r] = 1;
                } else {
                    ok = 0;
                }
            }
        }
        if(ok && test) {
            assert(accumulate(vis.begin(), vis.end(), 0) == n);
            s.insert(test);
        }
    }

    cout << sz(s) << '\n';
    for(int x : s) cout << x << '\n';

    return 0;
}
