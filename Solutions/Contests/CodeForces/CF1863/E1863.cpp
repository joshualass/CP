
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    ll n, m, k; cin >> n >> m >> k;

    vector<ll> h(n);
    for(ll &x : h) cin >> x;

    vector<int> indegrees(n);
    vector<vector<int>> adj(n);

    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        indegrees[b]++;
    }

    queue<int> q;
    vector<ll> times(n);
    for(int i = 0; i < n; i++) {
        if(indegrees[i] == 0) {
            q.push(i);
        }
    }

    vector<array<ll,2>> sh(n);
    priority_queue<ll> pq;

    while(q.size()) {
        int t = q.front();
        q.pop();

        sh[t] = {((h[t] - times[t]) % k + k) % k, times[t]};
        pq.push({sh[t][0] + sh[t][1]});

        for(int c : adj[t]) {
            times[c] = max(times[c], times[t] + (k + h[c] - h[t]) % k);
            indegrees[c]--;
            if(indegrees[c] == 0) {
                q.push(c);
            }
        }

    }

    sort(sh.begin(), sh.end());
    ll res = LLONG_MAX;
    for(int i = 0; i < n; i++) {
        res = min(res, pq.top() - sh[i][0]);
        pq.push({sh[i][0] + sh[i][1] + k});
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}