#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, m, l; cin >> n >> m >> l;

    ll maxo = INT_MAX, oc = 0, s = 0;
    for(int i = 0; i < l; i++) {
        ll x; cin >> x;
        if(x & 1) {
            maxo = min(maxo, x);
            oc++;
        }
        s += x;
    }

    ll mo, me;
    if(oc) {
        if(oc & 1) {
            mo = s;
            me = s - maxo;
        } else {
            mo = s - maxo;
            me = s;
        }
    } else {
        mo = 0;
        me = s;
    }

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<array<int,2>> vis(n, {-1,-1});
    queue<array<int,2>> q;
    q.push({0,0});
    while(q.size()) {
        auto [i, d] = q.front();
        q.pop();
        if(vis[i][d & 1] != -1) continue;
        vis[i][d & 1] = d;
        for(int c : adj[i]) {
            q.push({c, d + 1});
        }
    }

    // cout << "vis : " << vis << '\n';

    for(int i = 0; i < n; i++) {   
        cout << (vis[i][0] != -1 && vis[i][0] <= me || vis[i][1] != -1 && vis[i][1] <= mo);
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}