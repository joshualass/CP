#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
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

void solve(int tc) {
    int n, m; cin >> n >> m;
    if(tc == 376) {
        cout << 'n'<<n<<'m'<<m;
    }
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        if(tc == 376) {
            cout << '(' << a << "," << b << ")";
        }
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> dists(n,-1);
    queue<pair<int,int>> q;
    q.push({0,0});
    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();
        if(dists[p.first] != -1) continue;
        dists[p.first] = p.second;
        for(int t : adj[p.first]) q.push({t,p.second + 1});
    }

    // cout << "dists : " << dists << '\n';

    int f; cin >> f;
    // if(tc==376) cout << "f"<<f;
    vector<int> a(f);
    for(int &x : a) {
        cin >> x;
        x--;    
        // if(tc==376)cout<<"x"<<x;
    }
    int k; cin >> k;
    set<int> brokie;
    for(int i = 0; i < k; i++) {
        int num; cin >> num;
        num--;
        // if(tc==376) cout <<"b"<<num;
        brokie.insert(num);
    }

    if(tc == 376) {

    }

    vector<int> nocaridx;
    vector<unordered_map<int,int>> graph(n*2+2);

    for(int i = 0; i < n; i++) {
        graph[i][i+n] = k;
    }

    for(int i = 0; i < f; i++) {
        if(brokie.count(i)) {
            nocaridx.push_back(a[i]);
        } else {
            vector<bool> vis(n);
            queue<int> q;
            q.push(a[i]);
            while(q.size()) {
                int j = q.front();
                q.pop();
                if(vis[j]) continue;
                vis[j] = 1;
                for(int c : adj[j]) {
                    if(dists[j] - dists[c] == 1) {
                        // cout << "a[i] : " << a[i] << " add edge : " << c << " to " << j << '\n';

                        // graph[c][j]++;
                        graph[c + n][j]++;
                        q.push(c);
                    }
                }
            }
        }
    }

    int source = n * 2, sink = n * 2 + 1;
    graph[source][0] = k;

    int res = 0;

    for(int bm = 0; bm < 1 << k; bm++) {
        vector<unordered_map<int,int>> g = graph;
        set<int> s;
        for(int i = 0; i < k; i++) {
            if((bm >> i) & 1) {
                s.insert(nocaridx[i]);
            }
        }
        for(int idx : s) {
            int vnode = n + idx; //index of virtual node
            g[idx][sink]++; //add edge to node to sink
            g[source][vnode]++;
        }
        int flow = edmondsKarp(g,source,sink);
        if(flow == s.size()) {
            // cout << "bm is poss : " << bm << '\n'; //
            res = max(res, __builtin_popcount(bm));
        }
    }

    cout << k - res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc; cin >> tc;
    for(int i = 0; i < tc; i++) {
        solve(i);
    }

    return 0;
}