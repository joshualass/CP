// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// int m, n;
// int c, d;
// vector<vector<int>> adj;
// vector<vector<int>> trans;
// vector<pair<int,int>> order; 
// vector<bool> visited;
// stack<int> s;

// void DFS(int index) {
//     visited[index] = true;
//     for(int x : adj[index]) {
//         if(!visited[x]) {
//             if(index == c && x == d) {
//                 continue;
//             }
//             DFS(x);
//         }
//     }
//     if(index == d) {
//         if(!visited[c]) {
//             DFS(c);
//         }
//     }
//     s.push(index);
// }

// int DFS2(int index) {
//     visited[index] = true;
//     int total = 1;
//     for(int x : trans[index]) {
//         if(!visited[x]) {
//             if(index == d && x == c) {
//                 continue;
//             }
//             total += DFS2(x);
//         }
//     }
//     if(index == c) {
//         if(!visited[d]) {
//             total += DFS2(d);
//         }
//     }
//     return total;
// }

// bool solve() {
//     visited.assign(m,false);
//     while(s.size()) {
//         s.pop();
//     }
//     for(int i = 0; i < m; i++) {
//         if(!visited[i]) {
//             DFS(i);
//         }
//     }
//     visited.assign(m,false);
//     return DFS2(s.top()) == m;
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     // freopen("reversingroads.in","r",stdin);
//     int casi = 0;
//     cin >> m >> n; //m nodes n edges
//     while(!cin.eof() && cin.good()) {
//         // cout << "m: " << m << " n: " << n << "\n";
//         adj.assign(m,{});
//         trans.assign(m,{});
//         order.clear();
//         c = -1; d = -1;
//         for(int i = 0; i < n; i++) {
//             int a, b; cin >> a >> b;
//             adj[a].push_back(b);
//             trans[b].push_back(a);
//             order.push_back({a,b});
//         }
//         cout << "Case " << ++casi << ": ";
//         bool found = false;
//         if(solve()) {
//             cout << "valid";
//             found = true;
//         }
//         for(int i = 0; i < order.size() && !found; i++) {
//             c = order[i].first;
//             d = order[i].second;
//             if(solve()) {
//                 cout << c << " " << d;
//                 found = true; 
//             }  
//         }

        
//         cout << (found ? "" : "invalid") << "\n";
//         cin >> m >> n; //m nodes n edges
//     }

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

// void dfs(int i, vector<vector<int>> &adj, stack<int> &s, vector<int> &times, int &time, vector<vector<int>> &sccs,vector<int> &low, vector<bool> &vis) {
//     times[i] = time;    
//     low[i] = time++;
//     s.push(i);
//     vis[i] = 1;

//     for(int x : adj[i]) {
//         if(times[x] == -1) {
//             dfs(x,adj,s,times,time,sccs,low,vis);
//             low[i] = min(low[i], low[x]);
//         } else if(vis[x]) {
//             low[i] = min(low[i], times[x]);
//         }
//     }

//     if(low[i] == times[i]) {
//         sccs.push_back({});
//         while(1) {
//             int w = s.top();
//             s.pop();
//             vis[w] = 0;
//             sccs.back().push_back(w);
//             if(w == i) break;
//         }
//     }

// }

// vector<vector<int>> tarjans(vector<vector<int>> adj) {
//     int n = adj.size();
//     stack<int> s;
//     vector<int> times(n,-1);
//     vector<int> low(n);
//     vector<vector<int>> sccs;
//     vector<bool> vis(n);
//     int time = 0;
//     for(int i = 0; i < n; i++) {
//         if(times[i] == -1) {
//             dfs(i,adj,s,times,time,sccs,low,vis);
//         }
//     }
//     return sccs;
// }

void kdfs(int i, vector<vector<int>> &adj, vector<int> &order, vector<int> &vis) {
    vis[i] = 1;
    for(int x : adj[i]) {
        if(vis[x] == 0) {
            kdfs(x,adj,order,vis);
        }
    }
    order.push_back(i);
}

void sdfs(int i, vector<vector<int>> &adj, vector<int> &vis, vector<vector<int>> &sccs) {
    vis[i] = 2;
    sccs.back().push_back(i);
    for(int x : adj[i]) {
        if(vis[x] == 1) {
            sdfs(x,adj,vis,sccs);
        }
    }
}

vector<vector<int>> kosarajus(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<vector<int>> tp(n);
    for(int i = 0; i < n; i++) {
        for(int x : adj[i]) {
            tp[x].push_back(i);
        }
    }
    vector<int> order(n);
    vector<int> vis(n);
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            kdfs(i,adj,order,vis);
        }
    }
    reverse(order.begin(), order.end());
    vector<vector<int>> sccs;
    for(int i = 0; i < n; i++) {
        if(vis[order[i]] == 1) {
            sccs.push_back({});
            sdfs(order[i],tp,vis,sccs);
        }
    }
    return sccs;
}

vector<vector<int>> solve(vector<pair<int,int>> &a, int n) {
    vector<vector<int>> adj(n);
    for(int i = 0; i < a.size(); i++) {
        adj[a[i].first].push_back(a[i].second);
    }
    // return tarjans(adj);
    return kosarajus(adj);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    int t = 1;
    while(!cin.eof()) {
        cout << "Case " << t++ << ": ";
        vector<pair<int,int>> a(m);
        for(int i = 0; i < m; i++) {
            cin >> a[i].first >> a[i].second;
        }
        if(solve(a,n).size() == 1) {
            cout << "valid\n";
            cin >> n >> m;
            continue;
        }
        bool found = 0;
        for(int i = 0; i < m; i++) {
            swap(a[i].first, a[i].second);
            if(solve(a,n).size() == 1) {
                cout << a[i].second << " " << a[i].first << '\n';
                found = 1;
                break;
            }
            swap(a[i].first, a[i].second);
        }   
        if(!found) {
            cout << "invalid\n";
        }
        cin >> n >> m;
    }

    return 0;
}
