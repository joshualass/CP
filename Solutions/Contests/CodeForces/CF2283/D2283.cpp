#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }    

    int k;

    if(n % 2 == 0) {
        k = n + 1;
    } else {

        auto is_covered = [&](int k, int x) -> int {

            vector<set<int>> here(n);
            int ok = 0;

            // cout << "k : " << k << " x : " << x << endl;
            k -= 2;

            auto dfs = [&](auto self, int i, int p) -> void {
                for(int c : adj[i]) {
                    if(c != p) {
                        self(self, c, i);
                    }
                }
                if(i == x) {
                    for(int c : adj[i]) {
                        if(!here[c].empty()) ok = 1;
                    }
                } else {
                    here[i].insert(i);
                    for(int c : adj[i]) {
                        if(c != p) {
                            if(sz(here[c]) > sz(here[i])) swap(here[i], here[c]);
                        }
                    }
                    for(int c : adj[i]) {
                        if(c != p) {
                            for(int y : here[c]) {
                                if(here[i].count(k - y)) {
                                    here[i].erase(k - y);
                                } else {
                                    here[i].insert(y);
                                }
                            }
                        }
                    }
                }
                // cout << "i : " << i << " here[i] : " << here[i] << endl;
            };

            dfs(dfs, x, -1);
            return ok;

        };

        if(is_covered(n + 2, 0)) k = n + 2;
        else if(is_covered(n + 1, n / 2)) k = n + 1;
        else k = n;
    }

    cout << k << '\n';

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