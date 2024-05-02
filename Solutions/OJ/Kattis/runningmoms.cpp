#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

vector<vector<int>> tarjans(vector<vector<int>> adj) {
    int n = adj.size();
    stack<int> s;
    vector<vector<int>> sccs;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<vector<int>> adj(10000);
    map<string,int> ids;
    for(int i = 0; i < n; i++) {
        string o, d; cin >> o >> d;
        if(ids.count(o) == 0) {
            int sz = ids.size();
            ids[o] = sz;
        }
        if(ids.count(d) == 0) {
            int sz = ids.size();
            ids[d] = sz;
        }

        adj[ids[o]].push_back(ids[d]);
    }


    vector<vector<int>> sccs = tarjans(adj);
    vector<bool> in_cycle(10000);

    for(int i = 0; i < sccs.size(); i++) {
        if(sccs[i].size() > 1) {
            for(int x : sccs[i]) {
                in_cycle[x] = 1;
            }
        }
    }
    cin.ignore();
    string start; cin >> start; 

    while(!cin.eof()) {
        bool found = 0;
        queue<int> q;
        q.push(ids[start]);
        vector<bool> vis(10000);
        while(q.size()) {
            int i = q.front();
            q.pop();
            if(vis[i]) continue;
            vis[i] = 1;
            if(in_cycle[i]) {
                found = 1;
                break;
            }
            for(int x : adj[i]) {
                if(vis[x] == 0) {
                    q.push(x);
                }
            }
        }
        cout << start << " " << (found ? "safe" : "trapped") << '\n';

        cin >> start;
    }

    return 0;
}