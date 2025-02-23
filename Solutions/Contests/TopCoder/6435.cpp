#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
class InterleavePal {
public:
    int longestPal(string s, string t) {

        int n = s.size(), m = t.size();
        vector dp(n+1,vector(n+1,vector(m+1,vector<int>(m+1))));

        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= m; j++) {
                dp[i][i][j][j] = 1;
                if(i < n) {
                    dp[i][i+1][j][j] = 1;
                }
                if(j < m) {
                    dp[i][i][j][j+1] = 1;
                }
            }
        }

        int res = 0;

        for(int total_len = 0; total_len <= n + m; total_len++) {
            for(int sl = 0; sl <= total_len; sl++) {
                int tl = total_len - sl;
                for(int i = 0; i + sl <= n; i++) {
                    for(int j = 0; j + tl <= m; j++) {
                        if(dp[i][i+sl][j][j+tl]) {
                            res = max(res,sl+tl);
                            if(i && i + sl < n && s[i-1] == s[i+sl]) {
                                dp[i-1][i+sl+1][j][j+tl] = 1;
                            }
                            if(i && j + tl < m && s[i-1] == t[j+tl]) {
                                dp[i-1][i+sl][j][j+tl+1] = 1;
                            }
                            if(j && i + sl < n && t[j-1] == s[i+sl]) {
                                dp[i][i+sl+1][j-1][j+tl] = 1;
                            }
                            if(j && j + tl < m && t[j-1] == t[j+tl]) {
                                dp[i][i+sl][j-1][j+tl+1] = 1;
                            }
                        }
                    }
                }
            }
        }
        return res;
    }
};
// SOLUTION_END

int main() {
  string arg0;
  getline(cin, arg0);
  string arg1;
  getline(cin, arg1);
  auto c = InterleavePal();
  int ret = c.longestPal(arg0, arg1);
  cout << ret;
}