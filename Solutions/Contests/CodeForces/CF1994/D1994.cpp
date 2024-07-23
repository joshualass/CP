#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int N = 2000;
int dsu[N];
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
        sizes[x] += sizes[y];
    } else {
        dsu[y] = x;
        sizes[x] += sizes[y];
    }
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }

    vector<array<int,2>> ops;

    for(int x = n - 1; x >= 1; x--) {
        vector<vector<int>> m(x);
        for(int i = 0; i < n; i++) {
            m[a[i]%x].push_back(i);
        }
        bool found = 0;
        for(int i = 0; i < x && !found; i++) {
            for(int j = 1; j < m[i].size() && !found; j++) {
                if(find(m[i][0]) != find(m[i][j])) {
                    ops.push_back({m[i][0], m[i][j]});
                    merge(m[i][0], m[i][j]);
                    found = 1;
                }
            }
        }
    }

    cout << "YES\n";
    for(int i = n - 2; i >= 0; i--) {
        cout << ops[i][0] + 1 << " " << ops[i][1] + 1 << '\n';   
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}