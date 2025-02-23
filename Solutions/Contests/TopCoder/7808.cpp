#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
class RoadsReorganization {
public:
    int minDaysCount(vector<string> kingdom) {
        int n = kingdom.size();
        vector<vector<int>> adj(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(kingdom[i][j] == '1') {
                    adj[i].push_back(j);
                }
            }
        }

        auto dfs = [&](auto self, int i, int p) -> array<int,2> {
            vector<array<int,2>> a;
            for(int c : adj[i]) {
                if(c != p) {
                    a.push_back(self(self,c,i));
                }
            }
            if(a.size() >= 2) {
                sort(a.begin(),a.end(), [](const auto &lhs, const auto &rhs) {
                    return lhs[0] - lhs[1] < rhs[0] - rhs[1];
                });
                int c1 = a.size() - 1, c2 = a.size() - 2;
                for(int i = 0; i < a.size(); i++) {
                    if(i < 1) {
                        c1 += a[i][0];
                    } else {
                        c1 += a[i][1];
                    }
                    if(i < 2) {
                        c2 += a[i][0];
                    } else {
                        c2 += a[i][1];
                    }
                }
                return {c1,c2};
            } else if(a.size() == 1) {
                return {a[0][0],a[0][0]};
            } else {    
                return {0,0};
            }
        };
        array<int,2> res = dfs(dfs, 0, -1);
        int mindestruct = min(res[0],res[1]);
        return mindestruct * 2 + 1;
    }
};
// SOLUTION_END

int main() {
  int n0; cin >> n0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vector<string> arg0(n0);
  for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
  auto c = RoadsReorganization();
  int ret = c.minDaysCount(arg0);
  cout << ret;
}