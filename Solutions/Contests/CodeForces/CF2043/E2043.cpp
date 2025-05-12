#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, m; cin >> n >> m;
    vector a(n, vector<int>(m)), b(n, vector<int>(m));
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : b) for(auto &y : x) cin >> y;

    vector rdep(n, vector<int>(30)), cdep(m, vector<int>(30));
    vector st(n,vector(m,vector<int>(30)));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int k = 0; k < 30; k++) {
                st[i][j][k] = (b[i][j] >> k) & 1;
                if(st[i][j][k]) {
                    rdep[i][k]++;
                } else {
                    cdep[j][k]++;
                }
            }
        }
    }

    queue<array<int,3>> q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 30; j++) {
            if(rdep[i][j] == 0) {
                // cout << "sijag push r i : " << i << " j : " << j << '\n';
                q.push({0, i, j});
            }
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < 30; j++) {
            if(cdep[i][j] == 0) {
                // cout << "sijag push c i : " << i << " j : " << j << '\n';
                q.push({1, i, j});
            }
        }
    }

    while(q.size()) {
        auto [t, s, k] = q.front();
        q.pop();

        // cout << "t : " << t << " s : " << s << " k : " << k << '\n';

        if(t == 0) {
            int i = s;
            for(int j = 0; j < m; j++) {
                if(st[i][j][k] != -1) {
                    if(st[i][j][k]) {
                        assert(0);
                    } else {
                        cdep[j][k]--;
                        if(cdep[j][k] == 0) {
                            q.push({1, j, k});
                        }
                    }
                    st[i][j][k] = -1;
                }
            }
        } else {
            int j = s;
            for(int i = 0; i < n; i++) {
                if(st[i][j][k] != -1) {
                    if(st[i][j][k]) {
                        rdep[i][k]--;
                        if(rdep[i][k] == 0) {
                            q.push({0, i, k});
                        }
                    } else {
                        assert(0);
                    }
                    st[i][j][k] = -1;
                }
            }
        }
    }

    int ok = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int k = 0; k < 30; k++) {
                if(!(st[i][j][k] == -1 || st[i][j][k] == ((a[i][j] >> k) & 1))) {
                    ok = 0;
                }
            }
        }
    }

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}