#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
class ChessMatch {
public:
    double bestExpectedScore(vector<int> teamA, vector<int> teamB, int lim) {
        int n = teamA.size();
        vector<ld> dp(1 << n, -1);
        dp[0] = 0;

        vector<vector<ld>> pc(n,vector<ld>(n));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                pc[i][j] = 1 / (1 + powl(10, ((ld)(teamB[j] - teamA[i])) / 400));
            }
        }

        for(int i = 0; i < 1 << n; i++) {
            if(dp[i] >= 0) {
                int lo = 4000;
                int popc = __builtin_popcount(i);
                for(int j = 0; j < n; j++) {
                    if((i >> j) & 1) lo = min(lo,teamA[j]);
                }
                for(int j = 0; j < n; j++) {
                    if(((i >> j) & 1) == 0 && lo + lim >= teamA[j]) {
                        dp[i + (1 << j)] = max(dp[i + (1 << j)], dp[i] + pc[j][popc]);
                    }
                }
            }
        }
        return dp[(1 << n) - 1];
    }
};