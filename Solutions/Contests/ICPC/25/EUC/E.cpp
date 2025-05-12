#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

const int inf = 1e9;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const vector<int> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<vi> treeJump(vi& P){
	int on = 1, d = 1;
	while(on < sz(P)) on *= 2, d++;
	vector<vi> jmp(d, P);
	rep(i,1,d) rep(j,0,sz(P))
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps){
	rep(i,0,sz(tbl))
		if(steps&(1<<i)) nod = tbl[i][nod];
	return nod;
}

int lca(vector<vi>& tbl, vi& depth, int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);
	a = jmp(tbl, a, depth[a] - depth[b]);
	if (a == b) return a;
	for (int i = sz(tbl); i--;) {
		int c = tbl[i][a], d = tbl[i][b];
		if (c != d) a = c, b = d;
	}
	return tbl[0][a];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n), tadj(n), eadj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> d(n), p(n), vis(n);

    {    
        queue<array<int,3>> q; // {i, par, d}
        q.push({n - 1, n - 1, 0});
        while(q.size()) {
            auto [i, par, dep] = q.front();
            q.pop();
            if(vis[i]) {
                eadj[i].push_back(par);
                eadj[par].push_back(i);
                continue;
            }
            vis[i] = 1;
            if(i != n - 1) {
                tadj[i].push_back(par);
                tadj[par].push_back(i);
            }
            d[i] = dep;
            p[i] = par;
            for(int c : adj[i]) if(vis[c] == 0) q.push({c, i, dep + 1});
        }
    }

    // cout << "adj\n" << adj << '\n';
    // cout << "tadj\n" << tadj << '\n';
    // cout << "eadj\n" << eadj << '\n';

    auto tbl = treeJump(p);

    auto add = [&](map<int,int> &m, int k, int v) -> void {
        //there exists an element with smaller key and larger value already
        if(m.upper_bound(k) != m.begin() && (--m.upper_bound(k))->second <= v) return;
        //erase all elements with larger key and larger value. 
        while(m.upper_bound(k) != m.end() && m.upper_bound(k)->second >= v) m.erase(m.upper_bound(k));
        m[k] = v;
    };

    vector<map<int,int>> a(n);
    vector<int> f(n);

    auto dfs0 = [&](auto self, int i, int p) -> void {
        int li = i;
        for(int c : tadj[i]) {
            if(c != p) {
                self(self, c, i);
                if(a[c].size() > a[li].size()) li = c;
            }
        }
        swap(a[i], a[li]);
        for(int c : tadj[i]) {
            for(auto [k, v] : a[c]) add(a[i], k, v);
        }
        
        for(int c : eadj[i]) {
            int anc = lca(tbl, d, i, c);
            int anc_d = d[anc];
            int cycle_size = 1 + d[i] + d[c];
            add(a[i], anc_d, cycle_size);
        }

        if(a[i].lower_bound(d[i]) != a[i].begin()) {
            auto [k, v] = *--a[i].lower_bound(d[i]);
            f[i] = v - d[i];
        } else {
            f[i] = inf;
        }
    }; 

    dfs0(dfs0, n - 1, n - 1);

    f[n-1] = 0;
    // cout << "f : " << f << '\n';

    // vector<int> dists(n, -1);
    // {
    //     queue<array<int,2>> q;
    //     q.push({0,0});
    //     while(q.size()) {
    //         auto [i, d] = q.front();
    //         q.pop();
    //         if(dists[i] != -1) continue;
    //         dists[i] = d;
    //         for(int c : adj[i]) q.push({c, d + 1});
    //     }
    // }

    // {    
    //     vector<vector<int>> rtop(n);
    //     vector<int> ind(n);
    //     for(int i = 0; i < n; i++) {
    //         for(int c : adj[i]) {
    //             if(d[c] < d[i]) {
    //                 rtop[c].push_back(i);
    //                 ind[i]++;
    //             }
    //         }
    //     }

    //     queue<int> q;

    //     for(int i = 0; i < n; i++) {
    //         if(ind[i] == 0) q.push(i);
    //     }

    //     vector<int> g(n, inf);
    //     g[n - 1] = 0;

    //     while(q.size()) {
    //         int x = q.front();
    //         q.pop();
    //         int ming = inf;
    //         for(int c : adj[x]) {
    //             ming = min(ming, g[c]);
    //         }
    //         if(x != n - 1) g[x] = max(f[x], 1 + ming);
    //         for(int c : rtop[x]) {
    //             ind[c]--;
    //             if(ind[c] == 0) q.push(c);
    //         }
    //     }

    //     cout << "g1 : " << g << '\n';
    
    // }

    vector<int> g(n, inf);
    vis.assign(n, 0);
    priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq;
    pq.push({0, n - 1});
    while(pq.size()) {
        auto [gval, i] = pq.top();
        pq.pop();
        if(vis[i]) continue;
        vis[i] = 1;
        g[i] = gval;
        for(int c : adj[i]) {
            pq.push({max(f[c], gval + 1), c});
        }
    }

    // cout << "g2 : " << g << '\n';

    cout << (g[0] >= inf ? -1 : g[0]) << '\n';

    return 0;
}