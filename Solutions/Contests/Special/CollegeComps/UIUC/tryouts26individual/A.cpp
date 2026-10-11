#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int N = 3e5;
int dsu[N];
int sizes[N], items[N];

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
    items[x] += items[y];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l; cin >> n >> l;

    dsubuild(l);

    for(int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;

        merge(u, v);
        u = find(u);
        if(sizes[u] != items[u]) {
            items[u]++;
            cout << "LADICA" << '\n';
        } else {
            cout << "SMECE" << '\n';
        }
    }

    return 0;
}
