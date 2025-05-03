#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> a(1 << n, vector<int>(1 << n));

    for(auto &x : a) for(auto &y : x) cin >> y;

    vector<array<int,2>> b;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            b.push_back({i,j});
        }
    }

    set<int> vis;

    for(int i = 0; i < 4; i++) {
        auto c = b;
        c.erase(c.begin() + i);
        for(int j = 0; j + 1 < 1 << n; j++) {
            for(int k = 0; k + 1 < 1 << n; k++) {
                set<int> cnt;
                for(int l = 0; l < 3; l++) {
                    cnt.insert(a[j+c[l][0]][k+c[l][1]]);
                }
                if(cnt.size() == 1 && (*cnt.begin())) vis.insert(*cnt.begin());
            }
        }
    }

    int z = 0;
    for(int i = 0; i < 1 << n; i++) for(int j = 0; j < 1 << n ;j++) if(a[i][j] == 0) z = 1;

    cout << (vis.size() == ((1 << (2 * n)) - 1) / 3 && z) << '\n';

    return 0;
}
