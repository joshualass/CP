#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll node [9000000][5];
int p = 0;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 9000000; i++) for(int j = 0; j < 2; j++) node[i][j] = -1;

    int q; cin >> q;
    ll z = 0;

    auto dfs = [&](auto self, int i, int l, int r, ll x) -> void {
        if(r - l == 1) {
            node[i][2]++;
            if(node[i][2] & 1) {
                node[i][3] += x;
            } else {
                node[i][4] += x;
            }
        } else {
            int m = (l + r) / 2;
            if(x < m) { //go [l, m)
                if(node[i][0] == -1) {
                    node[i][0] = ++p;
                }
                self(self, node[i][0], l, m, x);
            } else { //go [m, r)
                if(node[i][1] == -1) {
                    node[i][1] = ++p;
                }
                self(self, node[i][1], m, r, x);
            }

            int lc = node[i][0], rc = node[i][1];
            ll fsum = node[lc][3], ssum = node[lc][4];
            if(node[lc][2] & 1) {
                fsum += node[rc][4];
                ssum += node[rc][3];
            } else {
                fsum += node[rc][3];
                ssum += node[rc][4];
            }
            node[i][2] = node[lc][2] + node[rc][2];
            node[i][3] = fsum;
            node[i][4] = ssum;
        }
    };

    for(int i = 0; i < q; i++) {
        ll y; cin >> y;
        ll x = (y + z) % 1'000'000'000 + 1;
        dfs(dfs, 0, 1, 1'000'000'001, x);
        z = node[0][3];
        cout << z << '\n';
    }


    return 0;
}
