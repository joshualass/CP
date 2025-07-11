#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

// const int N = 2e5;
// int dsu[N];
// int sizes[N];
map<array<int,2>, array<int,2>> dsu;
map<array<int,2>, int> dir;

array<int,2> find(array<int,2> x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(array<int,2> x, array<int,2> y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    dir[x] |= dir[y];
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, k; cin >> h >> w >> k;

    vector<int> dx = {1, 1, 0, -1, -1, -1, 0, 1}, dy = {0, 1, 1, 1, 0, -1, -1, -1};

    for(int i = 0; i < k; i++) {
        int r, c; cin >> r >> c;
        array<int,2> x = {r, c};
        dsu[x] = x;
        int d = 0;
        if(r == h) d += 1 << 0;
        if(r == 1) d += 1 << 1;
        if(c == w) d += 1 << 2;
        if(c == 1) d += 1 << 3;
        dir[x] = d;
        for(int j = 0; j < 8; j++) {
            array<int,2> n = {r + dx[j], c + dy[j]};
            if(dsu.count(n)) merge(x, n);
        }
    }

    int res = 0;
    for(auto [k, v] : dir) {
        if(__builtin_popcount(v) >= 2 && v != 9 && v != 6) res = 1;
    }

    cout << (res ? "No" : "Yes") << '\n';

    return 0;
}
