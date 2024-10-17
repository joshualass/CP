#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, q; cin >> h >> w >> q;

    vector<set<int>> rows(h);
    vector<set<int>> cols(w);

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            rows[i].insert(j);
            cols[j].insert(i);
        }
    }

    int rc = 0;

    auto rem = [&](int r, int c) -> void {
        rows[r].erase(c);
        rc++;
        cols[c].erase(r);
    };

    for(int i = 0; i < q; i++) {
        int r, c; cin >> r >> c;
        r--; c--;
        if(rows[r].count(c)) {
            rem(r,c);
        } else {
            if(rows[r].lower_bound(c) != rows[r].end()) {
                rem(r, *rows[r].lower_bound(c));
            }

            if(rows[r].lower_bound(c) != rows[r].begin()) {
                rem(r, *--rows[r].lower_bound(c));
            }

            if(cols[c].lower_bound(r) != cols[c].end()) {
                rem(*cols[c].lower_bound(r), c);
            }

            if(cols[c].lower_bound(r) != cols[c].begin()) {
                rem(*--cols[c].lower_bound(r), c);
            }
        }
    }

    cout << h * w - rc << '\n';

    return 0;
}