#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w; cin >> h >> w;
    vector<string> board(h);
    for(auto &x : board) cin >> x;
    int loh = h, hih = -1, low = w, hiw = -1;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(board[i][j] == '#') {
                loh = min(loh, i);
                hih = max(hih, i);
                low = min(low, j);
                hiw = max(hiw, j);
            }
        }
    }

    int ok = 1;
    for(int i = loh; i <= hih; i++) {
        for(int j = low; j <= hiw; j++) {
            if(board[i][j] == '.') ok = 0;
        }
    }

    cout << (ok ? "Yes" : "No") << '\n';

    return 0;
}