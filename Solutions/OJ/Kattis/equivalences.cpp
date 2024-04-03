#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void dfs(int i, vector<vector<int>> &adj, stack<int> &s, vector<int> &times, int &time, vector<vector<int>> &sccs,vector<int> &low, vector<bool> &vis) {
    times[i] = time;    
    low[i] = time++;
    s.push(i);
    vis[i] = 1;

    for(int x : adj[i]) {
        if(times[x] == -1) {
            dfs(x,adj,s,times,time,sccs,low,vis);
            low[i] = min(low[i], low[x]);
        } else if(vis[x]) {
            low[i] = min(low[i], times[x]);
        }
    }

    if(low[i] == times[i]) {
        sccs.push_back({});
        while(1) {
            int w = s.top();
            s.pop();
            vis[w] = 0;
            sccs.back().push_back(w);
            if(w == i) break;
        }
    }

}

vector<vector<int>> tarjans(vector<vector<int>> adj) {
    int n = adj.size();
    stack<int> s;
    vector<int> times(n,-1);
    vector<int> low(n);
    vector<vector<int>> sccs;
    vector<bool> vis(n);
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(times[i] == -1) {
            dfs(i,adj,s,times,time,sccs,low,vis);
        }
    }
    return sccs;
}

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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }
    vector<vector<int>> sccs = tarjans(adj);
    // vector<vector<int>> sccs = kosarajus(adj);
    // // cout << "sccs\n" << sccs;
    vector<int> c(n);
    for(int i = 0; i < sccs.size(); i++) {
        for(int x : sccs[i]) {
            c[x] = i;
        }
    }
    vector<int> idg(sccs.size());
    vector<int> odg(sccs.size());
    for(int i = 0; i < n; i++) {
        for(int to : adj[i]) {
            if(c[to] != c[i]) {
                idg[c[to]]++;
                odg[c[i]]++;
            }
        }
    }
    if(sccs.size() == 1) {
        cout << "0\n";
        return;
    }
    int resi = count(idg.begin(), idg.end(), 0);
    int reso = count(odg.begin(), odg.end(), 0);
    // cout << "sccs size : " << sccs.size() << " resi : " << resi << " reso : " << reso << " ";
    cout << max(resi,reso) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // freopen("in.txt","r",stdin);
    // freopen("a.out","w",stdout);
    // int n; cin >> n;
    // cout << "n : " << n << '\n';   
    int casi; cin >> casi;
    while(casi-->0) solve();

    // cerr << "ok\n";

    return 0;
}