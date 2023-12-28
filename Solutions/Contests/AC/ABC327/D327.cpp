#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> a(m);
    vector<int> b(m);
    for(auto &x : a) cin >> x;
    for(auto &x: b) cin >> x;
    for(int i = 0; i < m; i++) {
        adj[a[i]-1].push_back(b[i]-1);
        adj[b[i]-1].push_back(a[i]-1);
    }

    vector<int> visited(n,-1);
    bool ok = 1;
    for(int i = 0; i < n; i++) {
        if(visited[i] == -1) {
            queue<pair<int,int>> q;
            q.push({i,0});
            while(q.size()) {
                pair<int,int> p = q.front();
                q.pop();
                int x = p.first;
                if(visited[x] != -1) {
                    if(visited[x] != p.second) {

                        ok = 0;
                        // cout << "no because of x : " << x << " p.second : " << p.second << '\n';
                    }
                } else {
                    // cout << "x : " << x << " visited : " << visited << '\n';
                    visited[x] = p.second;
                    for(int y : adj[x]) {
                        q.push({y,p.second ^ 1});
                        // cout << " x p.second  : " << x << " " << p.second << " calling : " << y << " " << (p.second ^ 1) << '\n';
                    }
                }
            }
        }
    }
    cout << (ok ? "Yes" : "No") << '\n';
    return 0;
}