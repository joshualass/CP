#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    if(n == 1) {
        cout << "0\n";
        return;
    }

    vector<unordered_set<int>> adj(n);
    vector<int> sizes(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].insert(b);
        adj[b].insert(a);
    }

    for(int i = 0; i < n; i++) {
        if(adj[i].size() == 2) {
            int a = *adj[i].begin();
            int b = (*++adj[i].begin());
            adj[a].erase(i);
            adj[i].erase(a);
            adj[i].erase(b);
            adj[b].erase(i);
            adj[a].insert(b);
            adj[b].insert(a);
        }
    }

    int maxdegree = 0;
    int ops = 0;
    for(int i = 0; i < n; i++) {
        int leafcnt = 0;
        for(int c : adj[i]) {
            if(adj[c].size() == 1) {
                leafcnt++;
            }
        }
        ops += max(0,leafcnt-1);
        maxdegree = max(maxdegree, (int) adj[i].size());
    }
    if(maxdegree == 1) {
        cout << "1\n";
        return;
    }
    cout << ops << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}