#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5;
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

void solve() {
    
    int m, n; cin >> m >> n;
    vector<array<int,3>> edges;
    for(int i = 0; i < n * (n - 1) / 2; i++) {
        int a, b, c; cin >> a >> b >> c;
        edges.push_back({a,b,c});
    }
    sort(edges.begin(), edges.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[2] < rhs[2];
    });

    m -= n;

    dsubuild(n);

    for(int i = 0; i < n * (n - 1) / 2; i++) {
        auto [a, b, c] = edges[i];
        if(find(a) != find(b)) {
            m -= c;
            merge(a, b);
        }
    }

    cout << (m >= 0 ? "yes" : "no") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}