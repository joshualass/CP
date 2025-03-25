#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

// SOLUTION_BEGIN
#include <bits/stdc++.h>
using namespace std;

class PeriodicTiling {
public:
    int minBlock(vector<string> part) {

        int res = INT_MAX;
        for(int tt = 0; tt < 2; tt++) {
            int r = part.size(), c = part[0].size();
            for(int x = 1; x <= r; x++) {
                for(int y = 1; y * x <= r * c; y++) {
                    for(int pc = 0; pc < y; pc++) {

                        vector<string> pattern(x, string(y, '.'));
                        int ok = 1;

                        for(int i = 0; i < r; i++) {
                            for(int j = 0; j < c; j++) {
                                int row = i % x;
                                int offset_cnt = i / x;
                                int undo_offset = (j - offset_cnt * pc + y * r * c) % y;
                                if(pattern[row][undo_offset] == '.') pattern[row][undo_offset] = part[i][j];
                                if(pattern[row][undo_offset] != part[i][j]) {
                                    ok = 0;
                                }
                            }
                        }

                        if(ok) {
                            res = min(res, x * y);
                        }

                    }
                }
            }

            vector<string> part_transpose(c, string(r,'-'));
            for(int i = 0; i < r; i++) {
                for(int j = 0; j < c; j++) {
                    part_transpose[j][i] = part[i][j];
                }
            }

        }

        return res;

    }
};
// SOLUTION_END

int main() {
  int n0; cin >> n0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vector<string> arg0(n0);
  for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
  auto c = PeriodicTiling();
  int ret = c.minBlock(arg0);
  cout << ret;
}