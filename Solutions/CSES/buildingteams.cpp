#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<int> team(n);
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    bool flag = true;
    for(int i = 0; i < n; i++) {
        if(team[i] == 0) {  
            queue<pair<int,int>> q;
            q.push({i,0});
            while(q.size()) {
                pair<int,int> p = q.front();
                q.pop();
                if(team[p.first] != 0) {
                    if(team[p.first] != ((p.second ^ 1) + 1)) {
                        flag = false;
                        break;
                    }
                } else {
                    team[p.first] = ((p.second ^1) + 1);
                    for(auto x : adj[p.first]) q.push({x,p.second^1});
                }
            }
        }
    }
    if(flag) {
        for(auto x : team) cout << x << " ";
        cout << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}