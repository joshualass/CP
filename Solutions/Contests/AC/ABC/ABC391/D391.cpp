#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, w; cin >> n >> w;
    vector<vector<array<int,2>>> a(w);
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        a[x].push_back({y,i});
    }
    for(int i = 0; i < w; i++) {
        sort(a[i].begin(), a[i].end());
    }

    vector<int> res(n,-1);
    int r = 0;
    while(1) {
        int ok = 1;
        int hi = 0;
        for(int i = 0; i < w; i++) {
            if(a[i].size() <= r) {
                ok = 0;
                break;
            }
            hi = max(hi, a[i][r][0]);
        }
        if(ok == 0) break;
        for(int i = 0; i < w; i++) {
            res[a[i][r][1]] = hi + 1;
        }
        r++;
    }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int t, b; cin >> t >> b;
        cout << (res[b-1] == -1 || res[b-1] > t ? "Yes" : "No") << '\n';
    }

    return 0;
}