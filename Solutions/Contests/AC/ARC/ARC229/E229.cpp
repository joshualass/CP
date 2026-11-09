#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int N = 2e5;
int dsu[3][N];

void dsubuild(int n = N) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < n; j++) {
            dsu[i][j] = j;
        }
    }
}

int find(int id, int x) {
    if(dsu[id][x] == x) {
        return x;
    }
    dsu[id][x] = find(id, dsu[id][x]);
    return dsu[id][x];
}

void merge(int id, int x, int y) {
    // if(id == 2) {
    //     cout << "merge 3 x : " << x << " y : " << y << endl;
    // }
    x = find(id, x);
    y = find(id, y);
    if(x == y) {
        return;
    }
    dsu[id][y] = x;
}

void solve() {
    
    int n, m; cin >> n >> m;

    dsubuild(n);

    for(int i = 0; i < m; i++) {
        int u, v, l; cin >> u >> v >> l;
        u--; v--; l--;
        merge(l, u, v);
    }

    // cout << "starter merges done" << endl;

    map<array<int,2>, vector<int>> g;
    for(int i = 0; i < n; i++) {
        int id1 = find(1, i), id2 = find(2, i);
        g[{id1, id2}].push_back(i);
    }

    // cout << "now merge 1 2 stuff" << endl;

    for(auto [ids, a] : g) {
        for(int i = 1; i < sz(a); i++) {
            merge(0, a[i-1], a[i]);
        }
    }

    // cout << "merge 3 all reachable things next" << endl;

    vector<int> res;
    for(int i = 0; i < n; i++) {
        if(find(0, 0) == find(0, i)) res.push_back(i + 1);
    }

    cout << sz(res) << '\n';
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}