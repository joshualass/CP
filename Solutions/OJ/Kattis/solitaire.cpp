#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {

    int n = 5, m = 9;
    vector<string> a(n);
    set<array<int,2>> pos;

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        for(int j = 0; j < m; j++) {
            if(a[i][j] == 'o') {
                pos.insert({i,j});
            }
        }
    }

    int best_peg = pos.size();
    vector<int> dx = {-1,1,0,0}, dy = {0,0,-1,1};

    auto dfs = [&](auto self, set<array<int,2>> s) -> void {
        best_peg = min(best_peg, (int) s.size());
        for(auto [x, y] : s) {
            for(int i = 0; i < 4; i++) {
                array<int,2> b = {x + dx[i], y + dy[i]};
                int nx = x + dx[i] * 2, ny = y + dy[i] * 2;
                if(s.count(b) && nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] != '#' && s.count({nx,ny}) == 0) {
                    set<array<int,2>> t = s;
                    t.erase({x, y});
                    t.erase(b);
                    t.insert({nx, ny});
                    self(self, t);
                }
            }
        }
    };

    dfs(dfs, pos);

    cout << best_peg << " " << pos.size() - best_peg << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}