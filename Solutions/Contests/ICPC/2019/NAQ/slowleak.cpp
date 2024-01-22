#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m, t, d;
    cin >> n >> m >> t >> d;
    vector<bool> is_pump(n, false);
    for(int i = 0; i < t; i++){
        int next;
        cin >> next;
        next --;
        is_pump[next] = true;
    }
    vector<vector<pair<int, ll>>> c(n, vector<pair<int, ll>>(0));
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        ll k;
        cin >> k;
        u --;
        v --;
        c[u].push_back({v, k});
        c[v].push_back({u, k});
    }
    vector<ll> max_cap(n, -1);
    priority_queue<pair<ll, pair<ll, int>>> q;  //{-distance, {capacity, i}}
    q.push({0, {d, 0}});
    ll ans = 1e18;
    while(q.size() != 0){
        ll dist = -q.top().first;
        ll cap = q.top().second.first;
        int cur = q.top().second.second;
        q.pop();
        if(max_cap[cur] >= cap) {
            continue;
        }
        max_cap[cur] = cap;
        if(cur == n - 1){
            ans = dist;
            break;
        }
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll next_dist = dist + c[cur][i].second;
            ll next_cap = cap - c[cur][i].second;
            if(next_cap < 0){
                continue;
            }
            if(is_pump[next]) {
                next_cap = d;
            }
            q.push({-next_dist, {next_cap, next}});
        }
    }
    if(ans == 1e18){
        cout << "stuck\n";
    }
    else {
        cout << ans << "\n";
    }

    return 0;
}