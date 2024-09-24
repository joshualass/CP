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