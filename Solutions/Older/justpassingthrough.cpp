#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int cost[501][501];
bool pass[501][501];
int dp[501][501][11];
bool visited[501][501][11];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C, N; cin >> R >> C >> N;
    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            cin >> cost[r][c];
        }
    }
    for(int c = 0; c < C; c++) {
        for(int r = 0; r < R; r++) {
            for(int p = 0; p <= 10; p++) {
                dp[r][c][p] = 1e9;
            }
        }
    }
    for(int r = 0; r < R; r++) {
        for(int c = 1; c < C-1; c++) {
            if(cost[r][c] == -1 || cost[r][c-1] == -1 || cost[r][c+1] == -1 || cost[r-1][c] == -1 || cost[r+1][c] == -1) {
                continue;
            }
            if(cost[r][c-1] < cost[r][c] && cost[r][c+1] < cost[r][c] && cost[r+1][c] > cost[r][c] && cost[r-1][c] > cost[r][c]) {
                pass[r][c] = true;
            }
        }
    }
    for(int c = 0; c < C; c++) {
        for(int r = 0; r < R; r++) {
            if(cost[r][c] == -1) {
                continue;
            }
            for(int p = 0; p <= N; p++) {
                if(c == 0) {
                    dp[r][c][0] = cost[r][c];
                    visited[r][c][0] = true;
                } else {
                    if(pass[r][c]) {
                        if(p == N) {
                            continue;
                        }
                        if(r != 0 && visited[r-1][c-1] && cost[r-1][c-1] != -1) {
                            dp[r][c][p+1] = min(dp[r][c][p+1],dp[r-1][c-1][p] + cost[r][c]);
                            visited[r][c][p+1] = true;
                        }
                        if(visited[r][c-1] && cost[r][c-1] != -1) {
                            dp[r][c][p+1] = min(dp[r][c][p+1],dp[r][c-1][p] + cost[r][c]);
                            visited[r][c][p+1] = true;
                        }
                        if(r != R-1 && visited[r+1][c-1] && cost[r+1][c-1] != -1) {
                            dp[r][c][p+1] = min(dp[r][c][p+1],dp[r+1][c-1][p] + cost[r][c]);
                            visited[r][c][p+1] = true;
                        }
                    } else {
                        if(r != 0 && visited[r-1][c-1] && cost[r-1][c-1] != -1) {
                            dp[r][c][p] = min(dp[r][c][p],dp[r-1][c-1][p] + cost[r][c]);
                            visited[r][c][p] = true;
                        }
                        if(visited[r][c-1] && cost[r][c-1] != -1) {
                            dp[r][c][p] = min(dp[r][c][p],dp[r][c-1][p] + cost[r][c]);
                            visited[r][c][p] = true;
                        }
                        if(r != R-1 && visited[r+1][c-1] && cost[r+1][c-1] != -1) {
                            dp[r][c][p] = min(dp[r][c][p],dp[r+1][c-1][p] + cost[r][c]);
                            visited[r][c][p] = true;
                        }                        
                    }
                }
            }
        }
    }
    int least = 1e9;
    for(int r = 0; r < R; r++) {
        if(visited[r][C-1][N]) {
            least = min(least, dp[r][C-1][N]);
        }
    }
    cout << (least == 1e9 ? "impossible" : to_string(least)) << "\n";

    return 0;
}