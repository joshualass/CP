// https://open.kattis.com/problems/taxicab
/*
Solution: Max-flow
find maximum flow from taxi end rides to taxi beginning rides
need to use dinic's algorithm bc it is faster here. 
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T>
T dinic(vector<vector<pair<int, T>>> c, int source, int sink) {
    int n = c.size();
    TIMER_ABSTIME ans = 0;
    //redo organization of edges
    vector<pair<int, T>> edges(0);
    vector<vector<int>> adj(n, vector<int>(0));
    int m = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j].first;
            ll cap = c[i][j].second;
            adj[u].push_back(m);
            adj[v].push_back(m + 1);
            edges.push_back({v, cap});
            edges.push_back({u, 0});
            m += 2;
        }
    }
    while(true) {
        //create level graph
        vector<int> level(n, -1);
        queue<int> q;
        vector<bool> v(n, false);
        v[source] = true;
        q.push(source);
        level[source] = 0;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < adj[cur].size(); i++) {
                int nEdge = adj[cur][i];
                int next = edges[nEdge].first;
                if(v[next]) {
                    continue;
                }
                if(edges[nEdge].second == 0){
                    //no flow
                    continue;
                }
                v[next] = true;
                q.push(next);
                level[next] = level[cur] + 1;
            }
        }
        if(!v[sink]){
            //we're done here
            break;
        }
        while(true) {
            //do dfs until there is no path from source to sink along level graph
            stack<int> s;
            s.push(source);
            stack<int> est;
            stack<int> ist;
            ist.push(0);
            while(s.size() != 0){
                int cur = s.top();
                if(cur == sink) {   
                    //we've found path from source to sink
                    break;
                }
                bool foundNext = false;
                for(int i = ist.top(); i < adj[cur].size(); i++){
                    int nEdge = adj[cur][i];
                    int next = edges[nEdge].first;
                    if(level[next] <= level[cur]){
                        continue;
                    }
                    if(edges[nEdge].second == 0){
                        continue;
                    }
                    s.push(next);
                    est.push(nEdge);
                    ist.pop();
                    ist.push(i + 1);
                    ist.push(0);
                    foundNext = true;
                    break;
                }
                if(!foundNext) {
                    s.pop();
                    ist.pop();
                    if(est.size() != 0){
                        est.pop();
                    }
                    //mark this node as a dead end
                    level[cur] = -1;
                }
            }
            if(s.size() != 0 && s.top() == sink) {
                //found a path yay, now we update flow for edges on path
                T bn = 1e18;
                vector<int> path(est.size(), 0);
                for(int i = 0; i < path.size(); i++){
                    path[i] = est.top();
                    est.pop();
                    bn = min(bn, edges[path[i]].second);
                }
                for(int i = 0; i < path.size(); i++){
                    //forward edge
                    edges[path[i]].second -= bn;
                    //backwards edge
                    edges[path[i] ^ 1].second += bn;
                }
                ans += bn;
            }
            else {
                //the maximum flow for this level configuration has been reached. 
                break;
            }
        }
    }
    return ans;
}

template<class T>
T edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vector<int> par(graph.size());
    vector<int> q = par;

    for(;;) {
        fill(par.begin(), par.end(), -1);
        par[source] = 0;
        int ptr = 1;
        q[0] = source;

        for(int i = 0; i < ptr; i++) {
            int x = q[i];
            for(auto e : graph[x]) {
                if(par[e.first] == -1 && e.second > 0) {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if(e.first == sink) goto out;
                }
            }
        }
    return flow;
out:
    T inc = numeric_limits<T>::max();
    for(int y = sink; y != source; y = par[y]) {
        inc = min(inc, graph[par[y]][y]);
    }

    flow += inc;
    for(int y = sink; y != source; y = par[y]) {
        int p = par[y];
        if((graph[p][y] -= inc) <= 0) {
            graph[p].erase(y);
        }
        graph[y][p] += inc;
        }
    }
}

int gettime(string &str) {
    return stoi(str.substr(0,2)) * 60 + stoi(str.substr(3,2));
}

int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void solve() {
    int m; cin >> m;

    vector<array<int,4>> starts; //time, id, x, y
    vector<array<int,4>> ends; //

    // vector<unordered_map<int,int>> graph(3 + m * 2); //0 - source, 1 - source bottleneck, 2 - sink
    vector<vector<pair<int,ll>>> graph(3 + m * 2);
    int id = 3;

    for(int i = 0; i < m; i++) {
        string str; cin >> str;
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        int start_time = gettime(str);
        int end_time = start_time + dist(x1,y1,x2,y2);
        starts.push_back({start_time, id++, x1, y1});
        // graph[1][starts.back()[1]] = 1;
        // graph[starts.back()[1]][2] = 1;
        graph[1].push_back({starts.back()[1],1});
        graph[starts.back()[1]].push_back({2,1});
        ends.push_back({end_time, id++, x2, y2});
        // graph[0][ends.back()[1]] = 1;
        graph[0].push_back({ends.back()[1],1});
    }

    for(array<int,4> end: ends) {
        for(array<int,4> start: starts) {
            int time = dist(end[2], end[3], start[2], start[3]);
            int difftime = start[0] - end[0];
            if(time < difftime) {
                // cout << "build edge : " << end[1] << " " << start[1] << '\n';
                // cout << "time : " << time << " difftime: " << difftime << '\n';
                // graph[end[1]][start[1]] = 1;
                graph[end[1]].push_back({start[1],1});
            }
        }
    }

    // int lo = 1, hi = 500;
    // while(lo != hi) { //searching for lowest lo that is valid
    //     // cout << "yikes binary search: " << lo << " " << hi << '\n';
    //     int M = (lo + hi) / 2;
    //     vector<unordered_map<int,int>> graph_copy = graph;
    //     graph_copy[0][1] = M;
    //     int flow = edmondsKarp(graph_copy,0,2);
    //     // cout << "flow : " << flow << " M : " << M << '\n';
    //     if(flow == m) {
    //         // cout << "possible : " << M << '\n';
    //         hi = M;
    //     } else {
    //         lo = M + 1;
    //         // cout << "not possible : " << M << '\n';
    //     }
    // }
    // cout << lo << '\n';
    // cout << m - edmondsKarp(graph,0,2) << '\n';
    cout << m - dinic(graph, 0, 2) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // freopen("c.in","r",stdin);
    // freopen(".out","w",stdout);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}