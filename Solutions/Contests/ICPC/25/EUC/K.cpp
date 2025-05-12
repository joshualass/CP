#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

// const int INF = numeric_limits<int>::max();

// bool bfs(const vector<vector<int>>& graph, const vector<int>& pairU, const vector<int>& pairV, vector<int>& dist) {
//     queue<int> q;
//     for (int u = 0; u < graph.size(); ++u) {
//         if (pairU[u] == -1) {
//             dist[u] = 0;
//             q.push(u);
//         } else {
//             dist[u] = INF;
//         }
//     }
//     dist[-1] = INF;
//     while (!q.empty()) {
//         int u = q.front();
//         q.pop();
//         if (u != -1) {
//             for (int v : graph[u]) {
//                 if (dist[pairV[v]] == INF) {
//                     dist[pairV[v]] = dist[u] + 1;
//                     q.push(pairV[v]);
//                 }
//             }
//         }
//     }
//     return dist[-1] != INF;
// }

// bool dfs(const vector<vector<int>>& graph, vector<int>& pairU, vector<int>& pairV, vector<int>& dist, int u) {
//     if (u != -1) {
//         for (int v : graph[u]) {
//             if (dist[pairV[v]] == dist[u] + 1 && dfs(graph, pairU, pairV, dist, pairV[v])) {
//                 pairV[v] = u;
//                 pairU[u] = v;
//                 return true;
//             }
//         }
//         dist[u] = INF;
//         return false;
//     }
//     return true;
// }

// int hopcroftKarp(const vector<vector<int>>& graph, int source, int sink) {
//     vector<int> pairU(graph.size(), -1);
//     vector<int> pairV(graph[0].size(), -1);
//     vector<int> dist(graph.size());
//     int matching = 0;
//     while (bfs(graph, pairU, pairV, dist)) {
//         for (int u = 0; u < graph.size(); ++u) {
//             if (pairU[u] == -1 && dfs(graph, pairU, pairV, dist, u)) {
//                 ++matching;
//             }
//         }
//     }
//     return matching;
// }

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	for (int e : g[di])
		if (!vis[e] && find(e, g, btoa, vis)) {
			btoa[e] = di;
			return 1;
		}
	return 0;
}
int dfsMatching(vector<vi>& g, vi& btoa) {
	vi vis;
	rep(i,0,sz(g)) {
		vis.assign(sz(btoa), 0);
		for (int j : g[i])
			if (find(j, g, btoa, vis)) {
				btoa[j] = i;
				break;
			}
	}
	return sz(btoa) - (int)count(all(btoa), -1);
}

vi cover(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = dfsMatching(g, match);
	vector<bool> lfound(n, true), seen(m);
	for (int it : match) if (it != -1) lfound[it] = false;
	vi q, cover;
	rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for (int e : g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}

void solve() {
    
    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}