#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void dfsh(int i, vector<vector<int>> &adj, vector<int> &h) {
    if(adj[i].empty()) {
        h[i] = 0;
        return;
    }
    for(int x : adj[i]) {
        dfsh(x,adj,h);
    }
    h[i] = h[adj[i].front()] ^ 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        adj[p].push_back(i);
    }
    vector<int> h(n,-1);
    dfsh(0,adj,h);

    map<ll,ll> evens;
    map<ll,ll> odds;
    ll evencnt = 0;
    ll oddcnt = 0;
    int overall = 0;
    for(int i = 0; i < n; i++) {
        if(h[i] == 0) {
            evens[a[i]]++;
            overall ^= a[i];
            evencnt++;
        } else {
            odds[a[i]]++;
            oddcnt++;
        }
    }

    ll res = 0;
    for(auto x : evens) {
        //try swapping stuffs on even to odd
        int needed = overall;
        needed ^= x.first;
        if(odds.count(needed)) {
            res += x.second * odds[needed];
        }
    }

    if(overall == 0) {
        res += evencnt * (evencnt - 1) / 2;
        res += oddcnt * (oddcnt - 1) / 2;
    }
    cout << res << '\n';
    return 0;
}