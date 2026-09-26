#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
    }

    int a, b; cin >> a >> b;
    a--; b--;
    vector<int> reach(n);

    auto add_reach = [&](int start) -> void {
        vector<int> vis(n);
        queue<int> q;
        q.push(start);
        while(q.size()) {
            int x = q.front();
            q.pop();
            if(vis[x]) continue;
            vis[x] = 1;
            reach[x]++;
            for(int to : adj[x]) q.push(to);
        }
    };

    add_reach(a);
    add_reach(b);

    for(int i = 0; i < n; i++) {
        if(reach[i] == 2) {
            cout << "yes\n" << i + 1 << '\n';
            return 0;
        }
    }

    cout << "no\n";

    return 0;
}
