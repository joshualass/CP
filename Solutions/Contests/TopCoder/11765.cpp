#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include<bits/stdc++.h>
typedef long long ll;
const ll MOD = 1e9 + 7;
class DengklekPaintingSquares {
public:
    int numSolutions(int N, int M) {
        int m = 1;
        for(int i = 0; i < M; i++) m *= 3;

        auto decrypt = [&](int mask) -> vector<int> {
            vector<int> res;
            for(int i = 0; i < M; i++) {
                res.push_back(mask % 3);
                mask /= 3;
            }
            return res;
        };

        auto get_next = [&](vector<int> &prev, int mask) -> int {
            int ok = 1;
            int res = 0;
            for(int i = M - 1; i >= 0; i--) {
                res *= 3;
                int isblk = (mask >> i) & 1;
                if(prev[i] == 1 && !isblk || prev[i] == 2 && isblk) ok = 0;
                if(isblk) {
                    int p = 0;
                    if(prev[i]) p ^= 1;
                    if(i != M - 1 && ((mask >> (i + 1)) & 1)) p ^= 1;
                    if(i && ((mask >> (i - 1)) & 1)) p ^= 1;
                    p ^= 1;
                    p++;
                    res += p;
                }
            }
            if(ok) return res;
            return -1;
        };

        vector<vector<int>> t(m);
        for(int i = 0; i < m; i++) {
            vector<int> prev = decrypt(i);
            for(int j = 0; j < 1 << M; j++) {
                int res = get_next(prev, j);
                if(res != -1) {
                    t[i].push_back(res);
                }
            }
        }

        vector<ll> dp(m), ndp(m);
        dp[0] = 1;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < m; j++) ndp[j] = 0;
            for(int j = 0; j < m; j++) {
                for(int to : t[j]) {
                    ndp[to] += dp[j];
                    if(ndp[to] >= MOD) ndp[to] -= MOD;
                }
            }
            swap(ndp,dp);
        }
        ll res = 0;
        for(int i = 0; i < m; i++) {
            vector<int> states = decrypt(i);
            if(count(states.begin(), states.end(), 1) == 0) res = (res + dp[i]) % MOD;
        }
        return res;
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
  auto c = DengklekPaintingSquares();
  int ret = c.numSolutions(arg0, arg1);
  cout << ret;
}