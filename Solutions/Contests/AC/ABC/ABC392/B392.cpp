#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> vis(n);
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        vis[x-1] = 1;
    }
    cout << count(vis.begin(), vis.end(), 0) << '\n';
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) cout << i + 1 << " ";
    }
    cout << '\n';

    return 0;
}
