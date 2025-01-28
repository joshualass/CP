#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<ll>> pr(n+1,vector<ll>(n+1)), pc(n+1,vector<ll>(n+1)), p(n+1, vector<ll>(n+1));
    vector a(n,vector<ll>(n));

    for(auto &x : a) for(auto &y : x) cin >> y;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + a[i-1][j-1];
            pr[i][j] = pr[i-1][j] + pr[i][j-1] - pr[i-1][j-1] + a[i-1][j-1] * i;
            pc[i][j] = pc[i-1][j] + pc[i][j-1] - pc[i-1][j-1] + a[i-1][j-1] * j;
        }
    }

    auto getp = [](ll x1, ll y1, ll x2, ll y2, vector<vector<ll>> &p) -> ll {
        return p[x2][y2] - p[x2][y1-1] - p[x1-1][y2] + p[x1-1][y1-1];
    };

    for(int i = 0; i < q; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        ll numrows = x2 - x1 + 1, numcols = y2 - y1 + 1;
        ll row_contrib = getp(x1,y1,x2,y2,pr) * numcols - getp(x1,y1,x2,y2,p) * x1 * numcols;
        ll col_contrib = getp(x1,y1,x2,y2,pc) - getp(x1,y1,x2,y2,p) * (y1-1);
        // cout << "row : " << row_contrib << " col : " << col_contrib << '\n';
        cout << row_contrib + col_contrib << " \n"[i == q - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}