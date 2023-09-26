#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T>
void printS(stack<T> x) {
    cout << "stack: ";
    while(x.size()) {
        cout << x.top() << ' ';
        x.pop();
    }
    cout << "\n";
}

void dfs(int i, int p, stack<int> &s, bool &found, vector<bool> &visited, vector<vector<int>> &adj) {
    if(found) return;
    s.push(i);
    if(visited[i]) {
        found = true;
    } else {
        visited[i] = true;
        for(auto x : adj[i]) {
            if(x != p) {
                dfs(x,i,s,found, visited, adj);
            }
        }
    }
    if(!found) s.pop();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<bool> visited(n);
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    stack<int> s;
    bool flag = false;
    for(int i = 0; i < n; i++) {
        if(!visited[i] && !flag) {
            dfs(i,-1, s, flag, visited, adj);
        }
    }
    if(flag) {
        // printS(s);
        vector<int> ans(1,s.top());
        s.pop();
        while(s.top() != ans.front()) {
            ans.push_back(s.top());
            s.pop();
        }
        ans.push_back(s.top());
        cout << ans.size() << "\n";
        for(auto x : ans) cout << ++x << " ";
        cout << endl;
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}