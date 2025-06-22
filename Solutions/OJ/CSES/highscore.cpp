#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<array<int,2>>> adj(n);
    vector<vector<int>> radj(n);

    for(int i = 0; i < m; i++) {
        int a, b, x; cin >> a >> b >> x;
        a--; b--;
        adj[a].push_back({b, x});
        radj[b].push_back(a);
    }

    vector<int> can_reach(n), can_reach2(n);
    queue<int> q;

    auto add_q = [&](int i) -> void {
        if(can_reach[i]) return;
        can_reach[i] = 1;
        q.push(i);
    };

    add_q(n - 1);
    while(q.size()) {
        int i = q.front();
        q.pop();
        for(int x : radj[i]) add_q(x);
    }

    auto add_q2 = [&](int i) -> void {
        if(can_reach2[i]) return;
        can_reach2[i] = 1;
        q.push(i);
    };

    add_q2(0);
    while(q.size()) {
        int i = q.front();
        q.pop();
        for(auto [to, w] : adj[i]) add_q2(to);
    }

    vector<ll> dists(n, -1e18);
    dists[0] = 0;

    auto relax = [&]() -> bool {
        int f = 0;
        for(int i = 0; i < n; i++) {
            for(auto [to, w] : adj[i]) {
                if(dists[i] + w > dists[to]) {
                    dists[to] = dists[i] + w;
                    if(can_reach[to] && can_reach2[to]) {
                        f = 1;
                    }
                }
            }
        }
        return f;
    };

    for(int i = 0; i < n * 2; i++) relax();

    cout << (relax() ? -1 : dists[n-1]) << '\n';

    return 0;
}
