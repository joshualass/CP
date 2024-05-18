#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<ld> probs(n);
    probs[n-1] = 1;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }
    for(int i = n - 2; i >= 0; i--) {
        vector<ld> bests(0);
        for(auto x : adj[i]) {
            bests.push_back(probs[x]);
        }
        if(adj[i].size()) {
            sort(bests.begin(),bests.end());

            // if(adj[i].size() & 1) {
            //     probs[i] = *max_element(bests.begin(),bests.end());
            // } else {
            //     sort(bests.begin(),bests.end());
            //     probs[i] = (bests[bests.size()-1] + bests[bests.size()-2]) / 2;
            // }
        }
    }
    cout << probs[0] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(15);
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}