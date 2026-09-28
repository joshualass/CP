#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 3e5;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
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
    dsu[y] = x;
    sizes[x] += sizes[y];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<set<int>> adj(n);
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    vector<array<int,2>> e(m);

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        e[i] = {u, v};
        adj[u].insert(v);
        adj[v].insert(u);
    }

    dsubuild();

    int q; cin >> q;
    int res = m;
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        x--;

        int b = find(e[x][0]), c = find(e[x][1]);

        if(b != c) {
            adj[b].erase(c);
            adj[c].erase(b);

            res -= adj[b].size();
            res -= adj[c].size();
            res--;

            if(adj[c].size() > adj[b].size()) swap(b, c);


            for(int x : adj[c]) {
                adj[x].erase(c);
                adj[x].insert(b);
                adj[b].insert(x);
            }

            merge(b, c);

            res += adj[b].size();
        }

        cout << res << '\n';

    }

    return 0;
}
