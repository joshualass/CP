#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll h, w, c, q; cin >> h >> w >> c >> q;

    vector<array<ll,3>> paints(q);

    for(auto &x: paints) for(auto &y: x) cin >> y;

    vector<ll> colors(c);
    vector<bool> rows_visited(h);
    vector<bool> cols_visited(w);
    int rows = 0;
    int cols = 0;

    for(int i = q - 1; i >= 0; i--) {
        if(paints[i][0] == 1) { //row
            int row = paints[i][1];
            row--;
            int color = paints[i][2] - 1;
            if(rows_visited[row] == 0) {
                colors[color] += w - cols;
                rows++;
                rows_visited[row] = 1;
            }
        } else if(paints[i][0] == 2) {
            int col = paints[i][1];
            col--;
            int color = paints[i][2] - 1;
            if(cols_visited[col] == 0) {
                colors[color] += h - rows;
                cols++;
                cols_visited[col] = 1;
            }
        }
    }

    for(auto x : colors) cout << x << " ";

    return 0;
}