#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
class CaseysArt {
public:
    double howManyWays(int length, int width) {
        vector<vector<int>> t(1 << width);

        for(int bm = 0; bm < 1 << width; bm++) {
            auto dfs = [&](auto self, int nextbm, int p, int l, int u) -> void {
                if(p == width) {
                    t[bm].push_back(nextbm);
                    return;    
                }
                l |= (bm >> p) & 1;

                if(p + 2 <= width) {
                    int nl = (bm >> (p + 1)) & 1;
                    if(l == 0 && nl == 0) {
                        if(u == 0) {
                            self(self, nextbm + (1 << p), p + 1, 1, 0);
                        }
                        self(self, nextbm + (1 << (p + 1)), p + 2, 0, 0);
                    }

                    if(l && u == 0 && ((bm >> (p + 1)) & 1) == 0) {
                        self(self, nextbm + (1 << p) + (1 << (p + 1)), p + 2, 0,0);
                    }

                    if(l == 0 && u == 0) {
                        self(self, nextbm + (1 << p) + (1 << (p + 1)), p + 1, 0, 1);
                    }
                }
                if(l) self(self, nextbm, p + 1, 0, 0);
            };
            dfs(dfs, 0, 0, 0, 0);
        }

        vector dp(length + 1, vector<double>(1 << width));
        dp[0][0] = 1;
        for(int i = 0; i < length; i++) {
            for(int j = 0; j < 1 << width; j++) {
                for(int to : t[j]) {
                    dp[i+1][to] += dp[i][j];
                }
            }
        }
        return dp[length][0];
    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg1;
  cin >> arg1;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = CaseysArt();
  double ret = c.howManyWays(arg0, arg1);
  cout << setprecision(numeric_limits<double>::max_digits10) << ret;
}