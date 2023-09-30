#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5;

vector<vector<ll>> adj[N];
ll v[N];
ll ans[N];

int dfs(ll &i, ll &p, int &b) {
    ll nodes = 0, cost = 0;
    for(auto &x : adj[i]) {
        if(p != x[0]) {
            if(x[1] == -1 && x[2] == -1) {
                ll cnt = dfs(x[0],i,b);
                x[1] = cnt;
                x[2] = 
            }
            nodes += x[1];
            cost += x[2];
        }
    }
    if(p != -1) {
        nodes++;
        cost += nodes * (v[i] ^ v[p]);
        // cout << "i: " << i << " p: " << p << " nodes: " << nodes << " cost: " << cost << "\n";
        return {nodes,cost};
    } else {
        ans[i] += cost;
        return {-1,-1};
    }
}

void solve() {
    int n; cin >> n;
    fill(begin(ans),begin(ans)+n,0);
    for(int i = 0; i < n; i++) {
        adj[i] = {};
    }
    for(int i = 0; i < n; i++) cin >> v[i];
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back({b,-1,-1});
        adj[b].push_back({a,-1,-1});
    }
    vector<pair<ll,ll>> order(0);
    for(int i = 0; i < n; i++) {
        order.push_back({adj[i].size(),i});
    }
    sort(order.begin(),order.end());
    for(int b = 0; b < 20; b++) {

        for(auto &o : order) dfs(o.second,-1);
    }
    for(int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}