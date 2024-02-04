#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<int> &x) {
    // cout << " --- vector --- ";
    for(int y : x) {
        cout << ++y << " ";
    }
    cout << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    
    vector<vector<int>> adj(n);
    vector<int> parents(n,-1);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    queue<pair<int,int>> q;
    q.push({0,-2});
    vector<int> ans(0);
    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();
        if(parents[p.first] == -1) {
            parents[p.first] = p.second;
        } else {
            continue;
        }
        if(p.first == n-1) {
            while(p.second != -2) {
                ans.push_back(p.first);
                p = {p.second, parents[p.second]};
                // cout << "f: " << p.first << " s: " << p.second << "\n";
            }
            break;
        }
        for(auto x : adj[p.first]) {
            q.push({x, p.first});
        }
    }
    
    // printV(parents);
    if(ans.size() == 0) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    ans.push_back(0);
    reverse(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    printV(ans);

    return 0;
}