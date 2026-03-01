#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int N = 2e5;
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

    int n; cin >> n;
    map<string,int> m;
    map<int, string> rm;
    vector<array<int,2>> adj(n);
    for(int i = 0; i < n; i++) {
        string l, r; cin >> l >> r;
        if(m.count(l) == 0) {
            int id = sz(m);
            m[l] = id;
            rm[id] = l;
        }
        if(m.count(r) == 0) {
            int id = sz(m);
            m[r]= id;
            rm[id] = r;
        }
        adj[i] = {m[l], m[r]};
    }

    dsubuild();

    for(auto [l, r] : adj) merge(r, l);
    for(auto [l, r] : adj) cout << rm[l] << " " << rm[find(l)] << '\n';

    return 0;
}
