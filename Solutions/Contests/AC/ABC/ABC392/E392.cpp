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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    dsubuild(n);

    vector<array<int,3>> a;
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        if(find(u) != find(v)) {
            merge(u, v);
        } else {
            a.push_back({i, u, v});
        }
    }

    set<int> s;
    for(int i = 0; i < n; i++) s.insert(find(i));

    vector<array<int,3>> res;

    for(auto [id, u, v] : a) {
        if(s.size() > 1) {
            int tv = find(v);
            s.erase(tv);
            int connect = *s.begin();
            s.erase(s.begin());

            merge(tv, connect);
            s.insert(find(connect));

            res.push_back({id + 1, v + 1, connect + 1});

        }
    }

    cout << res.size() << '\n';
    for(auto x : res) {
        for(auto y : x) cout << y << " ";
        cout << '\n';
    }

    return 0;
}
