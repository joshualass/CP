#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, n; cin >> h >> w >> n;

    vector<set<int>> r(h), c(w);

    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        r[x].insert(y);
        c[y].insert(x);
    }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int type, x; cin >> type >> x;
        x--;
        if(type == 1) {
            cout << r[x].size() << '\n';
            for(int y : r[x]) {
                c[y].erase(x);
            }
            r[x].clear();
        } else {
            cout << c[x].size() << '\n';
            for(int y : c[x]) {
                r[y].erase(x);
            }
            c[x].clear();
        }
    }


    return 0;
}
