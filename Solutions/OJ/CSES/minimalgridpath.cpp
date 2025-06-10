#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    string res; 
    res.push_back(a[0][0]);
    vector<vector<int>> vis(n, vector<int>(n));

    vector<int> dx = {0, 1}, dy = {1, 0};

    vis[0][0] = 1;
    for(int i = 0; i < (n - 1) * 2; i++) {
        char lo = 'Z';
        for(int c = max(0, i - n + 1); c <= min(n - 1, i); c++) {
            int r = i - c;
            if(vis[r][c]) {
                for(int k = 0; k < 2; k++) {
                    int nr = r + dx[k], nc = c + dy[k];
                    if(nr < n && nc < n) {
                        lo = min(lo, a[nr][nc]);
                    }
                }
            }
        }
        res.push_back(lo);
        for(int c = max(0, i - n + 1); c <= min(n - 1, i); c++) {
            int r = i - c;
            if(vis[r][c]) {
                for(int k = 0; k < 2; k++) {
                    int nr = r + dx[k], nc = c + dy[k];
                    if(nr < n && nc < n && a[nr][nc] == lo) {
                        vis[nr][nc] = 1;
                    }
                }
            }
        }
    }

    cout << res << '\n';

    return 0;
}
