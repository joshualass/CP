//https://judge.yosupo.jp/problem/unionfind

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 200000;
int dsu[N];
int depths[N];
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
        depths[x]++;
        sizes[x] += sizes[y];
    } else if(sizes[x] < sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[x] = y;
        sizes[y] += sizes[x];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        depths[i] = 1;
        sizes[i] = 1;
    }

    for(int i = 0; i < q; i++) {
        int a, b, c; cin >> a >> b >> c;
        // cout << "i: " << i << " a: " << a << " b: " << b << " c: " << c << "\n";
        if(a) {
            // cout << "finda: " << find(b) << " findb: " << find(c) << "\n";
            cout << (find(c) == find(b)) << "\n";
        } else {
            merge(c,b);
        }
    }

    return 0;
}