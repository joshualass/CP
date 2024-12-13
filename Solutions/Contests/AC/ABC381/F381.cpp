#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    vector<vector<vector<int>>> needed(20,vector<vector<int>>(2));
    vector<int> vis(1 << 20);
    int res = 0;

    auto addneed = [&](int bm) {
        if(vis[bm]) return;
        vis[bm] = 1;
        res = max(res, __builtin_popcount(bm));
        for(int i = 0; i < 20; i++) {
            if(((bm >> i) & 1) == 0) {
                needed[i][0].push_back(bm + (1 << i));
            }
        }
    };

    addneed(0);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        vector<int> c;
        swap(needed[x][1],c);
        swap(needed[x][0],needed[x][1]);
        for(int bm : c) {
            addneed(bm);
        }
    }

    cout << res * 2 << '\n';

    return 0;
}