#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> adj(n); // 0-indexed
    vector<bool> visited(n, false);
    for(int i = 0; i < m; i++) {
        ll a,b,c;
        cin >> a >> b >> c;
        adj[a-1].push_back({b - 1, c}); //index, weight
    }
    


    return 0;
}