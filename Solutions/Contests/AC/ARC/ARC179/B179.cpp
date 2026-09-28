#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
const int MAXN = 1e4;

ll dp[MAXN + 1][1 << 10];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n; cin >> m >> n;
    vector<int> deps(m); //in order to place another i, deps[i] must have also been placed
    vector<vector<int>> rdeps(m); //when we place i, all the deps that are satisfied
    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        num--;
        deps[i] = num; 
        rdeps[num].push_back(i);
    }



    //0 - dependency is not set, 1 - dependency is set
    //almighty push dp
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i = 0; i < n; i++) {
        for(int bm = 0; bm < 1 << m; bm++) {
            for(int j = 0; j < m; j++) { //try to place j
            // cout << "ok ?\n";
                if(((bm >> j) & 1) == 0) { //== has higher precendence than & :O
                    // cout << "okie dokie urokodaki!\n";
                    int nextbm = bm | (1 << j);
                    for(int rdep : rdeps[j]) {
                        nextbm &= ((1 << m) - 1) - (1 << rdep);
                    }
                    dp[i+1][nextbm] += dp[i][bm];
                    // cout << "do things...\n";
                    if(dp[i+1][nextbm] >= MOD) {
                        dp[i+1][nextbm] -= MOD;
                    }
                }
            }
        }
    }

    ll res = 0;
    for(int bm = 0; bm < 1 << m; bm++) {
        res += dp[n][bm];
    }

    cout << res % MOD << '\n';
    

    return 0;
}