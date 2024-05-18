#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int MAXN = 2e5;

int low[MAXN];
int times[MAXN];
bool vis[MAXN];

void dfs(int i, vector<vector<int>> &adj, stack<int> &s, int &time, vector<vector<int>> &sccs) {
    times[i] = time;    
    low[i] = time++;
    s.push(i);
    vis[i] = 1;

    for(int x : adj[i]) {
        if(times[x] == -1) {
            dfs(x,adj,s,time,sccs);
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

vector<vector<int>> tarjans(vector<vector<int>> adj, vector<vector<int>> &sccs) {
    int n = adj.size();
    stack<int> s;
    fill(times, times + n, -1);
    fill(low, low + n, 0);
    fill(vis, vis + n, 0);
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(times[i] == -1) {
            dfs(i,adj,s,time,sccs);
        }
    }
    return sccs;
}

void dfs(int i, vector<vector<int>> &adj, vector<bool> &vis) {
    vis[i] = 1;
    for(auto to : adj[i]) {
        if(vis[to] == 0) {
            dfs(to,adj,vis);
        }
    }
}

bool checker(vector<vector<pair<int,int>>> &adj, int n, int k) {
    vector<vector<int>> uadj(n);
    for(int i = 0; i < n; i++) {
        for(auto p : adj[i]) {
            uadj[i].push_back(p.first);
            if(p.second <= k) {
                uadj[p.first].push_back(i);
            }
        }
    }
    // vector<vector<int>> sccs = tarjans(uadj);
    vector<vector<int>> sccs;
    tarjans(uadj,sccs);
    vector<int> ids(n);
    for(int i = 0; i < sccs.size(); i++) {
        for(int x : sccs[i]) {
            ids[x] = i;
        }
    }
    vector<vector<int>> nadj(sccs.size());
    vector<int> idgs(sccs.size());
    for(int i = 0; i < n; i++) {
        for(int x : uadj[i]) {
            if(ids[i] != ids[x]) {
                nadj[ids[i]].push_back(ids[x]);
                idgs[ids[x]]++;
            }
        }
    }
    int start = -1;
    for(int i = 0; i < sccs.size(); i++) {
        if(idgs[i] == 0) start = i;
    }
    vector<bool> vis(sccs.size());
    dfs(start, nadj, vis);
    return count(vis.begin(), vis.end(), 1) == sccs.size();
}

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    vector<int> weights(1,0);
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v,w});
        weights.push_back(w);
    }

    if(!checker(adj,n,1e9)) {
        cout << "-1\n";
        return;
    }
    sort(weights.begin(), weights.end());
    int lo = 0, hi = m;
    while(lo != hi) {
        int M = (lo + hi) / 2;
        bool b = checker(adj,n,weights[M]);
        // cout << "k : " << weights[M] << " b : " << b << '\n';
        if(b) {
            hi = M;
        } else {
            lo = M + 1;
        }
    }
    cout << weights[lo] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}