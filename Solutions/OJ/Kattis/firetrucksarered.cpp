#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<int,vector<int>> m;
    vector<vector<int>> adj(n);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        for(int j = 0;j < x; j++) {
            int y; cin >> y;
            m[y].push_back(i);
            adj[i].push_back(y);
        }
    }

    vector<array<int,3>> res;
    vector<int> vis(n);

    vis[0] = 1;
    queue<int> q;
    q.push(0);

    while(q.size()) {
        int i = q.front();
        q.pop();

        for(int num : adj[i]) {
            for(int x : m[num]) {
                if(vis[x] == 0) {
                    res.push_back({i, x, num});
                    q.push(x);
                    vis[x] = 1;
                }
            }
            m[num] = {};
        }

    }

    // cout << "sz : " << res.size() << '\n';


    if(res.size() == n - 1) {
        for(array<int,3> a : res) {
            cout << a[0] + 1 << " " << a[1] + 1 << " " << a[2] << '\n';
        }
    } else {
        cout << "impossible\n";
    }

    return 0;
}