#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;
 
// ll dinic(int n, vector<vector<pair<int, ll>>> c, int source, int sink) {
//     ll ans = 0;
//     //redo organization of edges
//     vector<pair<int, ll>> edges(0);
//     vector<vector<int>> adj(n, vector<int>(0));
//     int m = 0;
//     for(int i = 0; i < n; i++){
//         for(int j = 0; j < c[i].size(); j++){
//             int u = i;
//             int v = c[i][j].first;
//             ll cap = c[i][j].second;
//             adj[u].push_back(m);
//             adj[v].push_back(m + 1);
//             edges.push_back({v, cap});
//             edges.push_back({u, 0});
//             m += 2;
//         }
//     }
//     while(true) {
//         //create level graph
//         vector<int> level(n, -1);
//         queue<int> q;
//         vector<bool> v(n, false);
//         v[source] = true;
//         q.push(source);
//         level[source] = 0;
//         while(q.size() != 0){
//             int cur = q.front();
//             q.pop();
//             for(int i = 0; i < adj[cur].size(); i++) {
//                 int nEdge = adj[cur][i];
//                 int next = edges[nEdge].first;
//                 if(v[next]) {
//                     continue;
//                 }
//                 if(edges[nEdge].second == 0){
//                     //no flow
//                     continue;
//                 }
//                 v[next] = true;
//                 q.push(next);
//                 level[next] = level[cur] + 1;
//             }
//         }
//         if(!v[sink]){
//             //we're done here
//             break;
//         }
//         while(true) {
//             //do dfs until there is no path from source to sink along level graph
//             stack<int> s;
//             s.push(source);
//             stack<int> est;
//             stack<int> ist;
//             ist.push(0);
//             while(s.size() != 0){
//                 int cur = s.top();
//                 if(cur == sink) {   
//                     //we've found path from source to sink
//                     break;
//                 }
//                 bool foundNext = false;
//                 for(int i = ist.top(); i < adj[cur].size(); i++){
//                     int nEdge = adj[cur][i];
//                     int next = edges[nEdge].first;
//                     if(level[next] <= level[cur]){
//                         continue;
//                     }
//                     if(edges[nEdge].second == 0){
//                         continue;
//                     }
//                     s.push(next);
//                     est.push(nEdge);
//                     ist.pop();
//                     ist.push(i + 1);
//                     ist.push(0);
//                     foundNext = true;
//                     break;
//                 }
//                 if(!foundNext) {
//                     s.pop();
//                     ist.pop();
//                     if(est.size() != 0){
//                         est.pop();
//                     }
//                     //mark this node as a dead end
//                     level[cur] = -1;
//                 }
//             }
//             if(s.size() != 0 && s.top() == sink) {
//                 //found a path yay, now we update flow for edges on path
//                 ll bn = 1e18;
//                 vector<int> path(est.size(), 0);
//                 for(int i = 0; i < path.size(); i++){
//                     path[i] = est.top();
//                     est.pop();
//                     bn = min(bn, edges[path[i]].second);
//                 }
//                 for(int i = 0; i < path.size(); i++){
//                     //forward edge
//                     edges[path[i]].second -= bn;
//                     //backwards edge
//                     edges[path[i] ^ 1].second += bn;
//                 }
//                 ans += bn;
//             }
//             else {
//                 //the maximum flow for this level configuration has been reached. 
//                 break;
//             }
//         }
//     }
//     return ans;
// }

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

//you're fixed at location 0, friends location is passed in. 
unordered_map<int, vector<int>> m;
bool check_valid(vector<int>& x, vector<int>& y, int circ, int loc, int n, int ptr, vector<int> &y_node, vector<int> &f_node) {
    int ssource = ptr ++;
    int ssink = ptr ++;
    // vector<vector<pair<int, ll>>> c(ptr);
    Dinic dinics(ptr, ssource, ssink);
    for(int i = 0; i < n; i++) {
        int p0 = (loc + y[i]) % circ;
        int p1 = (loc + circ - y[i]) % circ;
        vector<int> locs = {p0, p1};
        bool found = 0;
        for(int j = 0; j < 2; j++){
            int pos = locs[j];
            if(m.find(pos) == m.end()) {
                continue;
            }
            for(int k = 0; k < m[pos].size(); k++){
                // c[y_node[m[pos][k]]].push_back({f_node[i], 1});
                dinics.add_edge(y_node[m[pos][k]], f_node[i], 1);
                found = 1;
            }
        }
        if(!found) return 0;
    }
    for(int i = 0; i < n; i++){
        // c[ssource].push_back({y_node[i], 1});
        // c[f_node[i]].push_back({ssink, 1});
        dinics.add_edge(ssource, y_node[i], 1);
        dinics.add_edge(f_node[i], ssink, 1);
    }
    return dinics.flow() == n;
}
 
int mirror(int x, int c) {
    bool odd = false;
    if(c % 2 == 1){
        odd = true;
        x *= 2;
        c *= 2;
    }
    if(x >= c / 2){
        x -= (x - (c / 2)) * 2;
    }
    else {
        x += ((c / 2) - x) * 2;
    }
    if(odd){
        x /= 2;
    }
    return x;
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, c;
    cin >> n >> c;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
        m[x[i]].push_back(i);
        m[c - x[i]].push_back(i);
    }
    int miny = 1e9;
    for(int i = 0; i < n; i++){
        cin >> y[i];
        miny = min(miny, y[i]);
    }
    // cout << "1 " << mirror(1, c) << "\n";
    set<int> works;
    int ptr = 0;
    vector<int> y_node(n), f_node(n);
    for(int i = 0; i < n; i++){
        y_node[i] = ptr ++;
        f_node[i] = ptr ++;
    }
    for(int i = 0; i < n; i++){
        int p0 = (x[i] + miny) % c;
        int p1 = (x[i] + c - miny) % c;
        vector<int> t = {p0, p1};
        for(int j = 0; j < t.size(); j++){
            if(check_valid(x, y, c, t[j], n, ptr, y_node, f_node)) {
                works.insert(t[j]);
                works.insert(mirror(t[j], c) % c);
                // cout << "WORKS : " << t[j] << " " << mirror(t[j], c) << "\n";
            }
        }
    }
    cout << works.size() << "\n";
    
    return 0;
}