#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 1e5;

bool visited[N];

void bfs(int i, vector<vector<int>> &adj, vector<int> &res) {
    visited[i] = true;
    for(auto x : adj[i]) {
        res[x]--;
        if(!visited[x] && res[i] == 0) {
            bfs(x,adj,res);
        }
    }
}

void bfs2(int i, vector<vector<int>> &adj, vector<int> &res, vector<int> &ans) {
    ans.push_back(i);
    if(visited[i]) {
        return;
    }
    visited[i] = true;
    for(auto x : adj[i]) {
        if(res[x] != 0) {
            bfs2(x,adj,res,ans);
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> res(n);
    for(int i = 0; i < m; i++) {
        int a,b;cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        res[b]++;
    }

    for(int i = 0; i < n; i++) {
        if(!visited[i] && res[i] == 0) {
            bfs(i,adj,res);
        }
    }
    vector<int> ans(0);
    fill(begin(visited),begin(visited)+N,false);
    for(int i = 0; i < n; i++) {
        if(res[i] != 0) {
            bfs2(i,adj,res,ans);
            break;
        }
    }
    if(ans.size()) {
        // for(auto x : ans) cout << ++x << " ";
        bool flag = false;
        for(int i = 0; i < ans.size(); i++) {
            if(ans[i] == ans[ans.size()-1]) {
                flag = true;
            }
            if(flag) cout << ans[i] << " ";
        }
        cout << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }
    return 0;
}