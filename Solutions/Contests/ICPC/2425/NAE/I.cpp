#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++) cin >> g[i];
    vector<int> dr = {-1, -1, -1, 0, 0, 1, 1, 1};
    vector<int> dc = {-1, 0, 1, -1, 1, -1, 0, 1};
    vector<pair<int, int>> ans;
    for(int i = 1; i < n - 1; i++){
        for(int j = 1; j < m - 1; j++){
            if(g[i][j] != '0') continue;
            bool cvalid = true;
            for(int k = 0; k < 8; k++){
                int nr = i + dr[k], nc = j + dc[k];
                if(g[nr][nc] != 'O') cvalid = false;
            }
            if(cvalid) ans.push_back({i, j});
        }
    }
    if(ans.size() == 0) cout << "Oh no!\n";
    else if(ans.size() > 1) cout << "Oh no! " << ans.size() << " locations\n";
    else cout << ans[0].first + 1 << " " << ans[0].second + 1 << "\n";

    return 0;
}