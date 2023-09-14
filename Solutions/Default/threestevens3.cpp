#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int m; cin >> m;
        vector<vector<int>> adj(m,vector<int>(0));
        for(int i = 0; i < m; i++) {
            int n; cin >> n;
            adj[i].resize(n);
            for(int &x: adj[i]) cin >> x;
        }
        set<int> gone;
        vector<int> out(m);
        bool flag = true;
        for(int i = m-1; i >= 0; i--) {
            bool found = false;
            for(int r = 0; r < adj[i].size(); r++) {
                if(gone.find(adj[i][r]) == gone.end()) {
                    out[i] = adj[i][r];
                    found = true;
                }
                gone.insert(adj[i][r]);
            }
            if(!found) {
                flag = false;
                break;
            }
        }
        if(flag) {
            for(int x : out) cout << x << " ";
            cout << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}