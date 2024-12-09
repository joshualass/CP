#include <iostream>
using namespace std;
const long long MOD = 1e9 + 7;

long long dp_increase[2000][2000], dp_decrease[2000][2000];

signed main() {

    int n, m; cin >> n >> m;
    
    long long res = 0;
    for(int i = 0; i < n; i++) {
        long long p = 0, d = 0;
        for(int j = 1; j < m; j++) {
            if(i) d = (dp_increase[i-1][j] + d) % MOD;
            p = (p + d) % MOD;
            dp_increase[i][j] = (p + 1) % MOD;
            res = (dp_increase[i][j] * (m - j) + res) % MOD;
        }
        long long c = 0, s = 0;
        for(int j = m - 1; j > 0; j--) {
            if(i) {
                c = (dp_decrease[i-1][j] + c) % MOD;
            }
            s = (s + c) % MOD;
            dp_decrease[i][j] = s;
            res = (dp_decrease[i][j] + res) % MOD;
            if(i) {
                s = (dp_increase[i-1][j] * (m - j) + s) % MOD;
                c = (dp_increase[i-1][j] * (m - j) + c) % MOD;
            }
        }
    }

    cout << res << '\n';

    return 0;
}