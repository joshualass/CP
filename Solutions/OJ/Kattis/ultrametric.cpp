#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 1e5;
int dsu[N];
int sizes[N];

void dsubuild(int n) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

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


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    dsubuild(n);

    map<int,vector<array<int,2>>> edges;
    for(int i = 0; i < m; i++) {
        int u, v, l; cin >> u >> v >> l;
        edges[l].push_back({u,v});   
    }

    int ok = 1;

    for(auto [w, edge_w] : edges) {
        for(auto [u, v] : edge_w) if(find(u) == find(v)) ok = 0;
        for(auto [u, v] : edge_w) merge(u, v);
    }

    cout << (ok ? "possibly ultrametric" : "not ultrametric") << '\n';

    return 0;
}