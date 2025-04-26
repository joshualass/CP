#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
for a given tree state, if there exists a selection of nodes with 3+ moves, then there exists a node with a forced 1 move left. 

given several sets, find the largest value of an element in a set such that there exists a larger value in another set. 
just do things 3 times for this special case. 
*/

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> sm(n); //stores largest value node, so that there is another move available 

    auto dfsu = [&](auto self, int i, int p) -> void {



    };


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}