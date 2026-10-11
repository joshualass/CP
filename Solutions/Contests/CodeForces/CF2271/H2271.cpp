#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, x, y; cin >> n >> x >> y;
    x--; y--;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> a;
    auto dfs = [&](auto self, int i, int p) -> array<int,2> {

        vector<array<int,2>> b;
        int chosen = -1, s = 1;
        for(int c : adj[i]) {
            if(c != p) {
                b.push_back(self(self, c, i));
                if(b.back()[1]) {
                    chosen = c;
                }
                s += b.back()[0];
            }
        }

        if(chosen != -1 && i != x) {
            int unreach = 1;
            int idx = 0;
            for(int c : adj[i]) {
                if(c != p) {
                    if(c != chosen) {
                        unreach += b[idx][0];
                    }
                    idx++;
                }
            }
            int reach = n - unreach;
            a.push_back(reach & 1);
        }
        
        return {s, chosen != -1 || i == y};
    };

    dfs(dfs, x, x);

    cout << "a : " << a << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}