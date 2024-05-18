#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll ans;

//return max value of subtree that won't be deleted during compression
ll udfs(int i, int p, vector<vector<int>> &adj, vector<ll> &v) {

    vector<ll> children;
    for(int c : adj[i]) {
        if(c != p) {
            children.push_back(udfs(c,i,adj,v));
        }
    }

    sort(children.rbegin(), children.rend());
    //cases where we don't consider parent tree
    //best 2 children delete i, best child use i, best 3+ children use i, just use i
    if(children.size() >= 3) {
        ll s = 0;
        for(int i = 0; i < children.size() && (i < 3 || children[i] >= 0); i++) {
            s += children[i];
        }
        ans = max(ans, v[i] + s);
    }
    if(children.size() >= 2) {
        ans = max(ans, children[0] + children[1]);
    }
    if(children.size()) {
        ans = max(ans, v[i] + children[0]); 
    }
    ans = max(ans, v[i]);

    //not deleted when either using 1 child and not current node, current node and no children, or 2+ children and current node
    if(children.size() >= 2) {
        ll s = 0;
        for(int i = 0; i < children.size() && (i < 2 || children[i] >= 0); i++) {
            s += children[i];
        }
        return max({children[0], v[i], s + v[i]});
    } else if(children.size() == 1) {
        return max(children[0], v[i]);
    } else {
        return v[i];
    }

}

void solve() {
    int n; cin >> n;
    vector<ll> v(n);

    for(auto &x : v) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ans = 0;
    udfs(0,-1,adj,v);
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}