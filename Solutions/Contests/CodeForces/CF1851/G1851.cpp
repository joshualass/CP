#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
BPE - just sort edges in order of maximum height from both endpoints, and queries by starting height + energy. 
Then we use dsu and add edges if they can be used. 
*/

const int N = 2e5;
int dsu[N];
int sizes[N];

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[y] = x;
        sizes[x] += sizes[y];
    }
}

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> h(n);

    for(int &x : h) cin >> x;

    vector<array<int,3>> edges;

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        edges.push_back({u, v, max(h[u], h[v])});
    }

    sort(edges.begin(), edges.end(), [](const auto &lhs, const auto &rhs) {
        return lhs[2] < rhs[2];
    });

    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }

    int q; cin >> q;
    vector<array<int,5>> queries;
    for(int i = 0; i < q; i++) {
        int a, b, e; cin >> a >> b >> e;
        a--; b--;
        queries.push_back({a,b,e, h[a] + e, i});
    }

    sort(queries.begin(), queries.end(), [] (const auto &lhs, const auto &rhs) {
        return lhs[3] < rhs[3];
    });

    vector<int> res(q);
    int ep = 0;
    for(int i = 0; i < q; i++) {
        while(ep != edges.size() && queries[i][3] >= edges[ep][2]) {
            merge(edges[ep][0], edges[ep][1]);
            ep++;
        }
        res[queries[i][4]] = find(queries[i][0]) == find(queries[i][1]);
    }

    for(int ans : res) {
        cout << (ans ? "Yes" : "No") << '\n';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}