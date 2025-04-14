#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
implementation exercise
source -> 1 weight to each club -> 1 weight to each member -> 1 weight edge of member to it's political party which also restricts that this member is elected only once -> restrict political party to not exceed half to sink
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, unordered_map<T,D> m) {
    for(auto &x: m) os << '(' << x.first << ", " << x.second << ") ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
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

void solve(bool f) {
    if(!f) cout << '\n';
    int n; cin >> n;

    vector<vector<string>> a(n);
    set<string> rs, ps, cs;

    for(int i = 0; i < n; i++) {
        vector<string> b(2);
        for(auto &x : b) cin >> x;
        rs.insert(b[0]);
        ps.insert(b[1]);
        int m; cin >> m;
        for(int j = 0; j < m; j++) {
            string x; cin >> x; 
            b.push_back(x);
            cs.insert(b.back());
        }
        a[i] = b;
    }

    map<string,int> rm, pm, cm;
    map<int,string> rrm, rpm, rcm;
    int id = 0;
    for(string x : rs) {
        rrm[id] = x;
        rm[x] = id++;
    }
    for(string x : ps) {
        rpm[id] = x;
        pm[x] = id++;
    }
    for(string x : cs) {
        rcm[id] = x;
        cm[x] = id++;
    }
    int s = id++;
    int t = id++;

    vector<unordered_map<int,int>> g(id);

    for(auto [cn, p] : cm) {
        g[s][p] = 1;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 2; j < a[i].size(); j++) {
            g[cm[a[i][j]]][rm[a[i][0]]] = 1;
        }
        g[rm[a[i][0]]][pm[a[i][1]]] = 1;
    }

    for(auto [pn, p] : pm) {
        g[p][t] = (cm.size() - 1) / 2;
    }

    auto [flow, trace] = edmondsKarp(g, s, t);

    // cout << "rcm : " << rcm << '\n';

    if(flow != cm.size()) {
        cout << "Impossible.\n";
    } else {
        // cout << "possible\n";
        // for(int i = 0; i < trace.size(); i++) {
        //     cout << "i : " << i << " trace[i] : " << trace[i] << '\n';
        // }
        for(auto [p, cn] : rcm) {
            for(auto [x, f] : trace[p]) {
                if(f > 0) {
                    cout << rrm[x] << " " << cn << '\n';
                }
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    bool first = 1;
    while(casi-->0) {
        solve(first);
        first = 0;    
    }

    return 0;
}