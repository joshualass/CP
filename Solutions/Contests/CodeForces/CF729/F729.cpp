#include <iostream> 
#include <vector>
using namespace std;

int dp[2][2066][71][71];
const int inf = 1e9;

signed main() {

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2066; j++) {
            for(int k = 0; k < 71; k++) {
                for(int l = 0; l < 71; l++) {
                    dp[i][j][k][l] = inf;
                }
            }
        }
    }

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        p[i] = a[i-1] + p[i-1];
    }

    auto trymove = [&](int i, int left_idx, int right_idx, int k) -> int {
        if(k > right_idx - left_idx + 1) return inf;
        if(i == 0) {
            return p[left_idx + k] - p[left_idx];
        } else {
            return p[right_idx - k + 1] - p[right_idx + 1];
        }
    };

    auto dfs = [&](auto self, int i, int j, int k, int l) -> void {
        int left_idx = j, right_idx = n - 1 - (i == 0 ? (j + k) : ((j - l) + k));
        int tryk = trymove(i, left_idx, right_idx, l);
        int tryk1 = trymove(i, left_idx, right_idx, l + 1);
        if(i == 0) {
            if(tryk != inf) {
                if(dp[1][j + l][k][l] == inf) {
                    self(self, 1, j + l, k, l);
                }
                tryk += dp[1][j+l][k][l];
            }
            if(tryk1 != inf) {
                if(dp[1][j+l+1][k][l+1] == inf) {
                    self(self, 1, j + l + 1, k, l + 1);
                }
                tryk1 += dp[1][j+l+1][k][l+1];
            }
        } else {
            if(tryk != inf) {
                if(dp[0][j][k][l] == inf) {
                    self(self, 0, j, k, l);
                }
                tryk += dp[0][j][k][l];
            }
            if(tryk1 != inf) {
                if(dp[0][j][k + 1][l+1] == inf) {
                    self(self, 0, j, k + 1, l + 1);
                }
                tryk1 += dp[0][j][k+1][l+1];
            }
        }
        if(tryk == inf && tryk1 == inf) {
            dp[i][j][k][l] = 0;
        } else if(tryk == inf) {
            dp[i][j][k][l] = tryk1;
        } else if(tryk1 == inf) {
            dp[i][j][k][l] = tryk;
        } else {
            if(i == 0) {
                dp[i][j][k][l] = max(tryk, tryk1);
            } else {
                dp[i][j][k][l] = min(tryk, tryk1);
            }
        }
    };

    dfs(dfs, 0, 0, 0, 1);

    cout << dp[0][0][0][1] << '\n';

    return 0;
}