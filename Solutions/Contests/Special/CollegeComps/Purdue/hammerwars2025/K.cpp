#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
I spent a while thinking about this problem, not having the idea factory in play. 

with the idea factory, we guess some amortized behavior. 

The intuition lead to approaches where we incrementally add elements, lazily updating the mex counts. 
We store for each mex, the range of left endpoints having this mex as well as the last time they were updated. ok now lazy. 

when we insert an element to the right. 
first we add an element having mex 0 ending at that point. 
then, we update the mexes while we can and we can simulate this bc each mex is only visited at most once !
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    array<int,2> def = {-1, -1};

    vector<int> vis(n, -1);
    vector<array<int,2>> b(n + 1, def);
    vector<int> upd(n + 1, -1);

    vector<ll> res(n + 1);

    //update upd so that it is up to date with things 
    auto upd_mex = [&](int mex, int r) -> void {
        if(b[mex] != def) {
            int len = b[mex][1] - b[mex][0] + 1;
            int dist = r - upd[mex];
            res[mex] += 1LL * len * dist;
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
            if(vis[x] < b[x][1]) {
                nx = {b[x][0], vis[x]};
                b[x][0] = vis[x] + 1;
            } else {
                nx = b[x];
                b[x] = def;
            }
            add_group(x + 1, nx[0], nx[1], r - 1);
            x++;
        }
    }

    for(int i = 0; i <= n; i++) {
        upd_mex(i, n - 1);
    }

    for(int i = 0; i <= n; i++) cout << res[i] << " \n"[i == n];

    return 0;
}
