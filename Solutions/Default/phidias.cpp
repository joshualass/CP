// https://dmoj.ca/problem/ioi04p4
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int dp[601][601];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int i = 0; i < 601; i++) {
        memset(dp[i], 0, sizeof(dp[i]));
    }

    int W, H; cin >> W >> H;

    int n; cin >> n;

    vector<pair<int,int>> tiles(n);

    for(auto &x : tiles) cin >> x.first >> x.second;
    //everything oriented by width, height
    for(int w = 1; w <= W; w++) {
        for(int h = 1; h <= H; h++) {
            for(pair<int,int> tile : tiles) {
                if(tile.first <= w && tile.second <= h) { //tile can fit here
                    dp[w][h] = max(dp[w][h], tile.first * tile.second + max(dp[w - tile.first][h] + dp[tile.first][h - tile.second], dp[w][h - tile.second] + dp[w - tile.first][tile.second]));
                }
            }
        }
    }

    cout << W * H - dp[W][H] << '\n';

    return 0;
}