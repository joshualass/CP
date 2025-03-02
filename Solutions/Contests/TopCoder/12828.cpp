#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;

class JumpingOnTheGrid {
public:
    long long maxEnergy(vector<string> grid, int E, int T) {

        int r = grid.size(), c = grid[0].size();

        vector<vector<ll>> a(r,vector<ll>(c));

        int sr = -1, sc = -1, er = -1, ec = -1;
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                char ch = grid[i][j];
                if(ch == '#') {
                    a[i][j] = -1;
                } else if(ch == '*') {
                    sr = i;
                    sc = j;
                } else if(ch == '$') {
                    er = i;
                    ec = j;
                } else if(ch >= '1' && ch <= '9') {
                    a[i][j] = ch - '0';
                } else if(ch >= 'a' && ch <= 'z') {
                    a[i][j] = ch - 'a' + 10;
                } else if(ch >= 'A' && ch <= 'Z') {
                    a[i][j] = ch - 'A' + 36;
                }
            }
        }

        vector<vector<vector<ll>>> sdp(r,vector<vector<ll>>(c, vector<ll>(r * c * 2 + 10, -1)));
        vector<int> dx = {-1,1,0,0}, dy = {0,0,-1,1};

        sdp[sr][sc][0] = E;
        for(int t = 0; t < r * c * 2 + 10 - 1; t++) {
            for(int i = 0; i < r; i++) {
                for(int j = 0; j < c; j++) {
                    if(sdp[i][j][t] != -1 && a[i][j] != -1) {
                        sdp[i][j][t+1] = max(sdp[i][j][t+1], sdp[i][j][t] + a[i][j]); //charge at cell
                        for(int d = 0; d < 4; d++) {
                            for(int k = 1; k < max(r,c); k++) {
                                int ni = i + dx[d] * k;
                                int nj = j + dy[d] * k;
                                if(ni >= 0 && ni < r && nj >= 0 && nj < c) {
                                    if(a[ni][nj] == -1 || sdp[i][j][t] - k * k < 0) break;
                                    sdp[ni][nj][t + 1] = max(sdp[ni][nj][t + 1], sdp[i][j][t] - k * k);
                                } else {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        vector<vector<vector<ll>>> tdp(r,vector<vector<ll>>(c, vector<ll>(r * c * 2 + 10, 1e18)));
        tdp[er][ec][0] = 0;
        for(int t = 0; t < r * c * 2 + 10 - 1; t++) {
            for(int i = 0; i < r; i++) {
                for(int j = 0; j < c; j++) {
                    if(tdp[i][j][t] != -1 && a[i][j] != -1) {
                        for(int d = 0; d < 4; d++) {
                            for(int k = 1; k < max(r,c); k++) {
                                int ni = i + dx[d] * k;
                                int nj = j + dy[d] * k;
                                if(ni >= 0 && ni < r && nj >= 0 && nj < c) {
                                    if(a[ni][nj] == -1) break;
                                    tdp[ni][nj][t + 1] = min(tdp[ni][nj][t + 1], tdp[i][j][t] + k * k);
                                } else {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        ll res = -1;
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                for(int time_reach = 0; time_reach < r * c * 2 + 10; time_reach++) {
                    if(sdp[i][j][time_reach] != -1) {
                        for(int time_back = 0; time_back < r * c * 2 + 10; time_back++) {
                            int charge_time = T - time_reach - time_back;
                            if(charge_time < 0) break;
                            res = max(res, sdp[i][j][time_reach] - tdp[i][j][time_back] + a[i][j] * charge_time);
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
  int n0; cin >> n0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vector<string> arg0(n0);
  for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
  int arg1;
  cin >> arg1;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg2;
  cin >> arg2;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = JumpingOnTheGrid();
  long long ret = c.maxEnergy(arg0, arg1, arg2);
  cout << ret;
}