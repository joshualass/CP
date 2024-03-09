#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q; cin >> n >> m >> q;
    vector<vector<ll>> dist(n,vector<ll>(n,(1e18)));

    for(int i = 0; i < m; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        dist[a][b] = min(dist[a][b],c);
        dist[b][a] = min(dist[b][a],c);
    }
    for(int i = 0; i < n; i++) dist[i][i] = 0;
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        if(dist[a][b] == 1e18) {
            cout << "-1\n";
        } else {
            cout << dist[a][b] << '\n';
        }
    }

    return 0;
}