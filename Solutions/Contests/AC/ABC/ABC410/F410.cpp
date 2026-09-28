#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    if(m > n) {
        vector<string> b(m);;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                b[i].push_back(a[j][i]);
            }
        }
        a = b;
        swap(n, m);
    }

    vector<vector<int>> p(n + 1, vector<int>(m + 1));

    auto get_p = [&](int l1, int r1, int l2, int r2) -> int {
        return p[r1][r2] - p[l1][r2] - p[r1][l2] + p[l1][l2];
    };

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + (a[i-1][j-1] == '#' ? 1 : -1);
        }
    }

    ll res = 0;

    vector<int> cnts(n * m * 2 + 1);
    vector<array<int,2>> qid(n * m * 2 + 1);

    auto add = [&](int val, array<int,2> id) -> void {
        val += n * m;
        if(qid[val] == id) {
            res += cnts[val]++;
        } else {
            qid[val] = id;
            cnts[val] = 1;
        }
    };

    for(int l = 0; l < m; l++) {
        for(int r = l + 1; r <= m; r++) {
            add(0, {l, r});
            for(int i = 1; i <= n; i++) {
                add(get_p(0, i, l, r), {l, r});
            }
        }
    }
    
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}