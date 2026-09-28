#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    
    int ok = 1;
    vector<int> vis(m);
    for(int i = 0; i < n; i++) {
        int f; cin >> f;
        f--;
        if(vis[f]) ok = 0;
        vis[f] = 1;
    }

    cout << (ok ? "Yes" : "No") << '\n';
    cout << (accumulate(vis.begin(), vis.end(), 0) == m ? "Yes" : "No") << '\n';

    return 0;
}
