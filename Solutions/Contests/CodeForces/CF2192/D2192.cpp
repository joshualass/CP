#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<vector<ll>> adj(n);
    for(ll i = 1; i < n; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> res(n);
    //returns {sum of the nodes in the subtree, normal cost, depth of node with largest depth}
    auto dfs = [&](auto self, ll i, ll p) -> array<ll,4> {
        vector<array<ll,4>> ch;
        ll cost_here = 0, sum_here = 0, max_c = 0;
        ll best_add = 0;
        for(ll c : adj[i]) {
            if(c != p) {
                ch.push_back(self(self, c, i));
                sum_here += ch.back()[0];
                cost_here += ch.back()[0] + ch.back()[1];
                ch.back()[2]++;
                max_c = max(max_c, ch.back()[2]);
                best_add = max(best_add, ch.back()[3]);
            }
        }
        vector<ll> pre(sz(ch)), s(sz(ch));
        for(ll i = 0; i < ch.size(); i++) {
            pre[i] = max(i ? pre[i-1] : 0LL, ch[i][2]);
        }
        for(ll i = sz(ch) - 1; i >= 0; i--) {
            s[i] = max(i == sz(ch) - 1 ? 0LL : s[i+1], ch[i][2]);
        }
        for(ll i = 0; i < sz(ch); i++) {
            ll max_other = 0;
            if(i) max_other = max(max_other, pre[i-1]);
            if(i + 1 < sz(ch)) max_other = max(max_other, s[i+1]);
            best_add = max(best_add, 1LL * max_other * ch[i][0]);
        }
        res[i] = cost_here + best_add;
        // cout << "i : " << i << " cost_here : " << cost_here << " sh : " << sum_here << " max d : " << max_c << " ba : " << best_add << endl;
        // cout << "pre : " << pre << endl;
        // cout << "s : " << s << endl;
        return {sum_here + a[i], cost_here, max_c, best_add};
    };

    dfs(dfs, 0, -1);

    for(ll i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}