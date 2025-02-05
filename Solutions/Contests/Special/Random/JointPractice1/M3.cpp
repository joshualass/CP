#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct MCMF {
    const ll INF = LLONG_MAX >> 2;

    struct Edge {
        int v;
        ll cap, flow, cost;
    };

    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<pair<int, int>> par;
    vector<int> in_q;
    vector<ll> dist, pi;

    MCMF(int n) : n(n), adj(n), dist(n), pi(n), par(n), in_q(n) {}

    void addEdge(int u, int v, ll cap, ll cost) {
        int idx = edges.size();
        edges.push_back({v, cap, 0, cost});
        edges.push_back({u, cap, cap, -cost});
        adj[u].push_back(idx);
        adj[v].push_back(idx ^ 1);
    }

    bool find_path(int s, int t) {
        fill(dist.begin(), dist.end(), INF);
        fill(in_q.begin(), in_q.end(), 0);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        in_q[s] = 1;

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            in_q[cur] = 0;

            for (int idx : adj[cur]) {
                Edge& e = edges[idx];
                int nxt = e.v;
                ll cap = e.cap, fl = e.flow, wt = e.cost;
                ll nxtD = dist[cur] + wt;

                if (fl >= cap || nxtD >= dist[nxt]) continue;

                dist[nxt] = nxtD;
                par[nxt] = {cur, idx};

                if (!in_q[nxt]) {
                    q.push(nxt);
                    in_q[nxt] = 1;
                }
            }
        }
        return dist[t] < INF;
    }

    pair<ll, ll> calc(int s, int t) {
        ll flow = 0, cost = 0;

        while (find_path(s, t)) {
            for (int i = 0; i < n; i++) {
                pi[i] = min(pi[i] + dist[i], INF);
            }

            ll f = INF;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                f = min(f, edges[i].cap - edges[i].flow);
            }

            flow += f;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                edges[i].flow += f;
                edges[i ^ 1].flow -= f;
            }
        }

        for (size_t i = 0; i < edges.size() / 2; i++) {
            cost += edges[i * 2].cost * edges[i * 2].flow;
        }

        return {flow, cost};
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector a(n,vector<int>(m)), b(n,vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> b[i][j];
            if((i == 0 || i == n - 1) && b[i][j]) b[i][j]--;
            if((j == 0 || j == m - 1) && b[i][j]) b[i][j]--; 
        }
    }

    // vector<vector<int>> vid(n,vector<int>(m-1)), hid(n-1,vector<int>(m)), nid(n,vector<int>(m));

    // int idp = 0;
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m - 1; j++) {
    //         vid[i][j] = idp++;
    //     }
    // }

    // for(int i = 0; i < n - 1; i++) {
    //     for(int j = 0; j < m; j++) {
    //         hid[i][j] = idp++;
    //     }
    // }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         nid[i][j] = idp++;
    //     }
    // }

    // int s = idp++;
    // int t = idp++;
    // int aux = idp++;

    // MCMF mcmf(idp);

    

    MCMF mcmf(n * m + n * (m - 1) + m * (n - 1) + 3);
    int s = n * m + n * (m - 1) + m * (n - 1);
    int t = s + 1;
    int aux = t + 1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int left = n * m + (i * (m - 1) + j - 1);
            int right = n * m + (i * (m - 1) + j);
            int down = n * m + n * (m - 1) + ((i - 1) * m + j);
            int up = n * m + n * (m - 1) + (i * m + j);
            int node = i * m + j;
            // cout << "left : " << left << " right : " << right << " up : " << up << " down : " << down << '\n';
            //edge from source to cell
            mcmf.addEdge(s,node,b[i][j],0);
            //add to left window
            if(j) mcmf.addEdge(node,left,1,0);
            //add to right window
            if(j != m - 1) mcmf.addEdge(node,right,1,0);
            //add down
            if(i) mcmf.addEdge(node,down,1,0);
            //add up
            if(i != n - 1) mcmf.addEdge(node,up,1,0);
        }
    }

    //L-R / vertical windows 
    for(int i = 0; i < n; i++) {
        for(int j = 1; j < m; j++) {
            int window = n * m + (i * (m - 1) + j - 1);
            mcmf.addEdge(window,t,1,0);
            if(!(j == 0 || j == m)) {
                mcmf.addEdge(window,aux,1,a[i][j] * a[i][j-1]);
            }
        }
    }

    //U-D / horizontal windows
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int window = n * m + (n * (m - 1)) + ((i - 1) * m + j);
            mcmf.addEdge(window,t,1,0);
            if(!(i == 0 || i == n)) {
                mcmf.addEdge(window,aux,1,a[i][j] * a[i-1][j]);
            }
        }
    }

    mcmf.addEdge(aux,t,50*50*2,0);

    auto [f, c] = mcmf.calc(s,t);
    // cout << "f : " << f << " c : " << c << '\n';
    cout << c << '\n';

    return 0;
}
//https://meet.google.com/eto-yiwx-frm christian.lim@icpc.global

