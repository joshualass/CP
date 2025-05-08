#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<bool> vb;

#define rep(i, a, b) for(int i = 0; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

struct DSU {
    vi par, sz;
    DSU(int n) {
        par = vi(n);
        sz = vi(n, 1);
        for(int i = 0; i < n; i++) par[i] = i;
    }
    int find(int x) {
        if(par[x] == x) return x;
        int ans = find(par[x]);
        par[x] = ans;
        return ans;
    }
    bool merge(int u, int v) {
        if(find(u) == find(v)) return false;
        int ru = find(u), rv = find(v);
        if(sz[ru] < sz[rv]) swap(ru, rv);
        sz[ru] += sz[rv];
        par[rv] = ru;
        return true;
    }
};

struct Edge{
    int weight, id, u, v;
    bool in_mst = false;
    Edge(int _weight, int _id, int _u, int _v){
        weight = _weight;
        id = _id;
        u = _u;
        v = _v;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<Edge> e;
    vb in_mst(m, false);
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u --, v --;
        e.push_back(Edge(w, i, u, v));
    }
    sort(e.begin(), e.end(), [](Edge& a, Edge& b) -> bool {
        if(a.weight == b.weight) return a.id < b.id;
        return a.weight < b.weight;
    });
    int ans = n - 1;
    DSU dsu(n);
    vector<pii> emst(0);
    vi emst_id(0);
    for(int i = 0; i < e.size(); i++){
        int id = e[i].id, u = e[i].u, v = e[i].v;
        if(dsu.merge(u, v)) {
            in_mst[id] = true;
            emst.push_back({u, v});
            emst_id.push_back(id);
            if(id < n - 1) ans --;
        }
    }
    cout << ans << "\n";
    //for each edge that is in the ST but not the MST, can fix it using one operation. 
    vector<set<int>> c(n);
    sort(e.begin(), e.end(), [](Edge& a, Edge& b) -> bool {
        return a.id < b.id;
    });
    for(int i = 0; i < n - 1; i++){
        int u = e[i].u, v = e[i].v;
        c[u].insert(v);
        c[v].insert(u);
    }
    for(int i = 0; i < n - 1; i++){
        if(!in_mst[i]) {
            //remove this edge, do connected component search
            int u = e[i].u, v = e[i].v;
            c[u].erase(v);
            c[v].erase(u);
            set<int> s;
            queue<int> q;
            vb vis(n, false);
            vis[v] = true;
            q.push(v);
            while(q.size() != 0){
                int cur = q.front();
                q.pop();
                s.insert(cur);
                for(int x : c[cur]) if(!vis[x]) vis[x] = true, q.push(x);
            }
            bool found = false;
            for(int j = 0; j < emst.size(); j++){
                int _u = emst[j].first, _v = emst[j].second;
                if(s.count(_u) ^ s.count(_v)) {
                    //this mst edge can be used. 
                    c[_u].insert(_v);
                    c[_v].insert(_u);
                    found = true;
                    cout << e[i].id + 1 << " " << emst_id[j] + 1 << "\n";
                    break;
                }
            }
            assert(found);
        }
    }

    return 0;
}