#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    array<int,2> def = {-1, -1};
    vector<int> vis(n, -1), upd(n + 1, -1);
    vector<array<int,2>> b(n + 1, def);
    vector<ll> res(n + 1);

    auto upd_mex = [&](int mex, int r) -> void {
        if(b[mex] != def) {
            int time = r - upd[mex];
            int len = b[mex][1] - b[mex][0] + 1;
            res[mex] += 1LL * time * len;
        }
        upd[mex] = r;
    };

    auto add_group = [&](int mex, int l, int r, int curr) -> void {
        upd_mex(mex, curr);
        if(b[mex] == def) {
            b[mex] = {l, r};
        } else {
            assert(b[mex][1] + 1 == l);
            b[mex][1] = r;
        }
    };

    for(int r = 0; r < n; r++) {
        int x = a[r];
        add_group(0, r, r, r - 1);
        vis[x] = r;
        upd_mex(x, r - 1);
        while(x < n && b[x] != def && vis[x] >= b[x][0]) {
            array<int,2> nx;
            if(vis[x] >= b[x][1]) {
                nx = b[x];
                b[x] = def;
            } else {
                nx = {b[x][0], vis[x]};
                b[x][0] = vis[x] + 1;
            }
            add_group(x + 1, nx[0], nx[1], r - 1);
            x++;
        }
    }

    for(int i = 0; i <= n; i++) upd_mex(i, n - 1);


    int mex = 0;
    for(int i = 0; i <= n; i++) {
        if(res[i]) {
            mex++;
        } else {
            break;
        }
    }

    cout << mex + 1 << '\n';

    return 0;
}
