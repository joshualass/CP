#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t; cin >> n >> t;
    vector<map<int,vector<array<int,2>>>> adj(n);
    for(int i = 0; i < t; i++) {
        int u, v, dep, arr; cin >> u >> v >> dep >> arr;
        u--; v--;
        adj[u][dep].push_back({v, arr});
    }

    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;
    ll res = LLONG_MAX;

    auto push_q = [&](ll node, ll arrive_time, ll wait_time) -> void {
        // cout << "n : " << node << " at : " << arrive_time << " wt : " << wait_time << endl;
        if(node == n - 1) res = min(res, wait_time);
        if(adj[node].lower_bound(arrive_time) != adj[node].end()) {
            ll time = adj[node].lower_bound(arrive_time)->first;
            pq.push({time, wait_time + (time - arrive_time), node});
        }
    };

    push_q(0, 0, 0);

    while(!pq.empty()) {
        auto [time, wait, node] = pq.top();
        pq.pop();

        // cout << "time : " << time << " wait : " << wait << " node : " << node << endl;


        if(adj[node].count(time)) {
            for(auto [who, when] : adj[node][time]) {
                push_q(who, when, wait);
            }
            adj[node].erase(time);
            push_q(node, time, wait);
        }
    }

    if(res == LLONG_MAX) res = -1;
    cout << res << '\n';

    return 0;
}
