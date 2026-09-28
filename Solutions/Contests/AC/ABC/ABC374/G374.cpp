#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
steps
1) find SCCs and compress the graph
2) topological sort and then greedy the flow on the edges. 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(int i = 0; i < adj.size(); i++) {
        os << "i : " << i << " to ---- ";
        auto x = adj[i];
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

    vector<vector<int>> adj(26);

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        adj[s[0] - 'A'].push_back(s[1] - 'A');
    }

    vector<vector<int>> sccs = tarjans(adj);
    vector<int> ids(26);
    n = sccs.size();

    for(int i = 0; i < n; i++) {
        for(int x : sccs[i]) {
            ids[x] = i;
        }
    }

    vector<vector<int>> adj2(n);
    vector<int> needsflow(n);
    vector<int> indegrees(n);

    for(int i = 0; i < 26; i++) {
        for(int to : adj[i]) {
            if(ids[i] != ids[to]) {
                adj2[ids[i]].push_back(ids[to]);
                indegrees[ids[to]]++;
            } else {
                needsflow[ids[i]] = 1;
            }
        }
    }

    vector<int> top_order;
    vector<int> r_top(n);
    queue<int> q;

    for(int i = 0; i < n; i++) {
        if(indegrees[i] == 0) {
            q.push(i);
        }
    }

    while(q.size()) {
        int i = q.front();
        r_top[i] = top_order.size();
        top_order.push_back(i);
        q.pop();

        for(int to : adj2[i]) {
            indegrees[to]--;
            if(indegrees[to] == 0) {
                q.push(to);
            }
        }

    }

    vector<vector<int>> adjt(n);
    vector<int> needsflowt(n);

    for(int i = 0; i < n; i++) {
        for(int to : adj2[i]) {
            adjt[r_top[i]].push_back(r_top[to]);
        }
        needsflowt[r_top[i]] = needsflow[i];
    }

    auto adjc = adjt;
    int res = 0;

    // cout << "adjt\n" << adjt;
    // cout << "needsflowt : " << needsflowt << '\n';

    vector<vector<int>> visitable(n,vector<int>(n));

    auto dfs = [&](auto self, int i, int p) -> void {
        if(visitable[p][i]) return;
        visitable[p][i] = 1;
        for(int c : adjc[i]) {
            self(self, c, p);
        }
    };

    for(int i = 0; i < n; i++) {
        dfs(dfs, i, i);
    }



    while(1) {
        int found = -1;
        for(int i = 0; i < n; i++) {
            if(adjt[i].size()) {
                found = i;
                break;
            }
        }

        if(found == -1) break;

        res++;

        while(1) {
            needsflowt[found] = 0;
            if(adjt[found].size()) {
                int next = adjt[found].back();
                adjt[found].pop_back();
                found = next;
            } else {
                int next = -1;
                for(int i = found + 1; i < n; i++) {
                    if(visitable[found][i] && adjt[i].size()) {
                        next = i;
                        break;
                    }
                }
                if(next != -1) {
                    found = next;
                } else {
                    break;
                }
            }
        }

    }

    cout << res + accumulate(needsflowt.begin(), needsflowt.end(), 0) << '\n';    


    return 0;
}