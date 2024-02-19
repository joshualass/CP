#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<pair<ll,vector<int>>> v(n);
    vector<pair<int,int>> order(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        v[a].second.push_back(b);
        v[b].second.push_back(a);
    }
    // for(auto &x : v) cin >> x.first;
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        order[i] = {v[i].first,i};
    }

    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    sort(order.rbegin(), order.rend());
    
    ll ops = 0;
    for(int i = 0; i < n; i++) {
        int j = order[i].second;
        ops += a[j];
        for(int u : v[j].second) {
            if(v[u].first < v[j].first) {
                a[u] += a[j];
            }
        }
    }
    cout << ops << '\n';
    return 0;
}