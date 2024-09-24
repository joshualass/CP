#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, unordered_map<T,D> m) {
    for(auto &x: m) os << '(' << x.first << ", " << x.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    // for(auto x : v) os << x << " ";
    for(int i = 0; i < v.size(); i++) {
        cout << "i : " << i << " um : " << v[i] << '\n';
    }
    return os;
}

template<class T>
pair<T,vector<unordered_map<int,T>>> edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vector<int> par(graph.size());
    vector<int> q = par;
    vector<unordered_map<int,T>> trace(graph.size());

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
    return {flow,trace};
out:
    T inc = numeric_limits<T>::max();
    for(int y = sink; y != source; y = par[y]) {
        inc = min(inc, graph[par[y]][y]);
    }

    flow += inc;
    for(int y = sink; y != source; y = par[y]) {
        int p = par[y];
        trace[p][y] += inc;
        if((graph[p][y] -= inc) <= 0) {
            graph[p].erase(y);
        }
        graph[y][p] += inc;
        trace[y][p] -= inc;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    for(int i = 0; i < n; i++) {
        cin >> b[i];
        b[i]--;
    }

    vector<int> agroups(n,-1), bgroups(n,-1);
    int aid = 0, bid = 0;
    for(int i = 0; i < n; i++) {
        if(agroups[i] == -1) {
            int p = i;
            while(agroups[p] == -1) {
                agroups[p] = aid;
                p = a[p];
            }
            aid++;
        }
    }

    for(int i = 0; i < n; i++) {
        if(bgroups[i] == -1) {
            int p = i;
            while(bgroups[p] == -1) {
                bgroups[p] = bid;
                p = b[p];
            }
            bid++;
        }
    }

    vector<unordered_map<int,int>> adj(n*2 + 2);
    int source = n * 2, sink = n * 2 + 1;

    for(int i = 0; i < n; i++) {
        adj[source][i] = 1;
        adj[i + n][sink] = 1;
        adj[agroups[i]][bgroups[i]+n] = 1;
    }

    auto [flow, trace] = edmondsKarp(adj,source,sink);

    cout << n - flow << '\n';

    // cout << "trace \n" << trace << '\n';

    vector<int> used(n,1);

    for(int i = 0; i < n; i++) {
        int dest = -1;
        for(auto [d, f] : trace[i]) {
            if(f == 1) {
                dest = d;
            }
        }
        // cout << "i : " << i << " dest : " << dest << '\n';
        if(dest != -1) {
            for(int j = 0; j < n; j++) {
                if(agroups[j] == i && bgroups[j] == dest - n) {
                    used[j] = 0;
                    break;
                }
            }
        }

    }

    for(int i = 0; i < n; i++) {
        if(used[i]) {
            cout << i + 1 << " ";
        }
    }

    cout << '\n';

    return 0;
}