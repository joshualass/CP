#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int N = 1000;
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

    int n, e, p; cin >> n >> e >> p;
    dsubuild(n);
    vector<array<ld,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    for(int i = 0; i < p; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        merge(u, v);
    }

    for(int i = 1; i < e; i++) {
        merge(0, i);
    }

    vector<pair<ld,array<int,2>>> edges;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            edges.push_back(pair<ld,array<int,2>>{sqrtl((a[i][0] - a[j][0]) * (a[i][0] - a[j][0]) + (a[i][1] - a[j][1]) * (a[i][1] - a[j][1])), {i, j}});
        }
    }

    sort(edges.begin(), edges.end());
    
    ld res = 0;
    for(auto [w, e] : edges) {
        auto [u, v] = e;
        if(find(u) != find(v)) {
            merge(u, v);
            res += w;
        }
    }

    cout << fixed << setprecision(10) << res << '\n';

    return 0;
}
