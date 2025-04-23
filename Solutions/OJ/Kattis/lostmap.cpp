#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2500;
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

    int n; cin >> n;
    vector<array<int,3>> a;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int w; cin >> w;
            a.push_back({w, i, j});
        }
    }

    dsubuild(n);

    sort(a.begin(), a.end());

    for(auto edge : a) {
        auto [w, i, j] = edge;
        if(find(i) != find(j)) {
            cout << i + 1 << " " << j + 1 << '\n';
            merge(i,j);
        }
    }

    return 0;
}
