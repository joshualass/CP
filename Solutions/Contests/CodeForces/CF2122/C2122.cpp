#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<array<int,2>> x(n), y(n);
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        x[i] = {a, i};
        y[i] = {b, i};
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    array<array<vector<int>, 2>, 2> c;

    vector<int> xid(n), yid(n);
    for(int i = 0; i < n; i++) {
        xid[x[i][1]] = i * 2 < n;
        yid[y[i][1]] = i * 2 < n;
    }

    for(int i = 0; i < n; i++) {
        c[xid[i]][yid[i]].push_back(i);
    }

    assert(c[0][0].size() == c[1][1].size());
    assert(c[0][1].size() == c[1][0].size());

    while(c[0][0].size()) {
        cout << c[0][0].back() + 1 << " " << c[1][1].back() + 1 << '\n';
        c[0][0].pop_back();
        c[1][1].pop_back();
    }

    while(c[0][1].size()) {
        cout << c[0][1].back() + 1 << " " << c[1][0].back() + 1 << '\n';
        c[0][1].pop_back();
        c[1][0].pop_back();
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}