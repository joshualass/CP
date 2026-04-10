#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s, t; cin >> n >> s >> t;
    
    vector<vector<int>> a(n, vector<int>(n));
    for(auto &x : a) {
        for(auto &y : x) cin >> y;
    }

    priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq;

    vector<int> dis(n, 1e9), vis(n);
    auto push_q = [&](int i, int d) -> void {
        if(d < dis[i]) {
            dis[i] = d;
            pq.push({d, i});
        }
    };

    push_q(s, 0);

    while(sz(pq)) {
        auto [d, i] = pq.top();
        pq.pop();
        if(vis[i]) continue;
        vis[i] = 1;
        for(int to = 0; to < n; to++) {
            push_q(to, d + a[i][to]);
        }
    }

    cout << dis[t] << '\n';

    return 0;
}
