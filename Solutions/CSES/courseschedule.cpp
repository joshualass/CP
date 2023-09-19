#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//requires - update N, fill in adj, empty order vector
const int N = 1e5;

int visited[N];

void dfs(int v, vector<vector<int>> &adj, vector<int> &order) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u])
            dfs(u, adj, order);
    }
    order.push_back(v);
}

void topological_sort(vector<vector<int>> &adj, vector<int> &order) {
    int n = adj.size();
    //option to check if it's DAG

    /*
    fill(begin(visited),begin(visited) + n, false);
    vector<int> res(n);
    stack<int> s;
    int cnt = 0;
    for(auto x : adj) for(auto y : x) res[y]++;
    for(int i = 0; i < n; i++) {
        if(res[i] == 0 && !visited[i]) {
            s.push(i);
            cnt++;
        }
        while(s.size()) {
            int x = s.top();
            s.pop();
            visited[x] = true;
            for(auto y : adj[x]) {
                res[y]--;
                if(res[y] == 0 && !visited[y]) {
                    s.push(y);
                    cnt++;
                }
            }
        }
    }
    if(cnt != n) return;

    */

    fill(begin(visited),begin(visited) + n, false);
    order.clear();
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i,adj,order);
    }
    reverse(order.begin(), order.end());
    return;
}

/*
const int N = 1e5;

int visited[N];

void topological(int i,vector<int> &order, vector<vector<int>> &adj, vector<vector<int>> &res) { //using bfs
    if(visited[i] == 1) {
        order.push_back(-1);
        return;
    } else if(visited[i] == 2) {
        return;
    }
    visited[i] = 1;
    for(auto x : res[i]) {
        topological(x,order,adj,res);
    }
    visited[i] = 2;
    order.push_back(i);
    for(auto x : adj[i]) {
        topological(x, order, adj, res);
    }
}
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> ans(0);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--;b--;
        adj[a].push_back(b);
    }
    topological_sort(adj,ans);
    if(ans.size() != n) {
        cout << "IMPOSSIBLE\n";
    } else {
        for(auto x: ans) cout << ++x << " ";
        cout << "\n";
    }

    return 0;
}