#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;
 
const int INF = numeric_limits<int>::max();

bool bfs(const vector<vector<int>>& graph, const vector<int>& pairU, const vector<int>& pairV, vector<int>& dist) {
    queue<int> q;
    for (int u = 0; u < graph.size(); ++u) {
        if (pairU[u] == -1) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[-1] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u != -1) {
            for (int v : graph[u]) {
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return dist[-1] != INF;
}

bool dfs(const vector<vector<int>>& graph, vector<int>& pairU, vector<int>& pairV, vector<int>& dist, int u) {
    if (u != -1) {
        for (int v : graph[u]) {
            if (dist[pairV[v]] == dist[u] + 1 && dfs(graph, pairU, pairV, dist, pairV[v])) {
                pairV[v] = u;
                pairU[u] = v;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroftKarp(const vector<vector<int>>& graph, int source, int sink) {
    vector<int> pairU(graph.size(), -1);
    vector<int> pairV(graph[0].size(), -1);
    vector<int> dist(graph.size());
    int matching = 0;
    while (bfs(graph, pairU, pairV, dist)) {
        for (int u = 0; u < graph.size(); ++u) {
            if (pairU[u] == -1 && dfs(graph, pairU, pairV, dist, u)) {
                ++matching;
            }
        }
    }
    return matching;
}
 
//you're fixed at location 0, friends location is passed in. 
map<int, vector<int>> m;
bool check_valid(vector<int>& x, vector<int>& y, int circ, int loc) {
    int n = x.size();
    int ptr = 0;
    vector<int> y_node(n), f_node(n);
    for(int i = 0; i < n; i++){
        y_node[i] = ptr ++;
        f_node[i] = ptr ++;
    }
    int ssource = ptr ++;
    int ssink = ptr ++;
    vector<vector<int>> c(ptr);
    for(int i = 0; i < n; i++) {
        int p0 = (loc + y[i]) % circ;
        int p1 = (loc + circ - y[i]) % circ;
        vector<int> locs = {p0, p1};
        for(int j = 0; j < 2; j++){
            int pos = locs[j];
            if(m.find(pos) == m.end()) {
                continue;
            }
            for(int k = 0; k < m[pos].size(); k++){
                c[y_node[m[pos][k]]].push_back(f_node[i]);
            }
        }
    }
    for(int i = 0; i < n; i++){
        c[ssource].push_back(y_node[i]);
        c[f_node[i]].push_back(ssink);
    }
    return hopcroftKarp(c, ssource, ssink) == n;
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
    for(int i = 0; i < n; i++){
        int p0 = (x[i] + miny) % c;
        int p1 = (x[i] + c - miny) % c;
        vector<int> t = {p0, p1};
        for(int j = 0; j < t.size(); j++){
            if(check_valid(x, y, c, t[j])) {
                works.insert(t[j]);
                works.insert(mirror(t[j], c) % c);
                // cout << "WORKS : " << t[j] << " " << mirror(t[j], c) << "\n";
            }
        }
    }
    cout << works.size() << "\n";
    
    return 0;
}