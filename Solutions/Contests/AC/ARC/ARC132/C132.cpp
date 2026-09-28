#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, d; cin >> n >> d;
    vector<vector<ll>> dp(n + 1, vector<ll>(1 << (1 + (d << 1))));

    vector<int> v(n); //Simon the digger. 
    vector<bool> fixed(n+1);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[i] = num;
        if(num != -1) {
            fixed[num] = true;
        }
    }

    dp[0][0] = 1; //1 way to have empty permutation
    for(int i = 0; i < n; i++) {
        if(v[i] == -1) {
            for(int j = 0; j < d * 2 + 1; j++) {
                int num = i + 1 - d + j; //num we are adding
                // cout << "i: " << i << " add num: " << num << '\n';
                int bottom = i + 1 - d;
                if(num < 1 || num > n) continue;
                for(int k = 0; k < dp[0].size(); k++) {//k represents current state
                    if(((k >> j) & 1) == 0 && ((k & 1) == 1 || fixed[bottom] || bottom < 1 || (k & 1) == 0 && j == 0)) {
                        //trying to put a number at j
                        // int num = 
                        if(dp[i][k]) {
                            // cout << "make the transition: " << i << " " << j << " " << k << " adding num: " << num << '\n';
                            int newk = k | (1 << j);
                            // cout << "newk: " << newk << '\n';
                            dp[i+1][newk >> 1] += dp[i][k];
                            dp[i+1][newk >> 1] %= MOD;
                            // cout << "next state: " << i + 1 << ", " << (newk >> 1) << " cnt: " << dp[i + 1][newk >> 1] << '\n';
                        }
                    }
                }
            } 
        } else {//fixed value
            int low = i + 1 - d;
            for(int j = 0; j < dp[i].size(); j++) {
                if(fixed[low] || (j & 1) || low < 1) {//check that the value is satisfied
                    // cout << "transition: " << j << " " << dp[i][j] << '\n';
                    // int newj = j | (1 << )
                    dp[i + 1][j >> 1] += dp[i][j]; //make transition
                    // cout << "upd idx: " << i + 1 << " " << (j >> 1) << " val: " << dp[i + 1][j >> 1] << '\n';
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < dp[0].size(); i++) {
        bool empty = false;
        for(int j = 0; j < d; j++) {
            int num = n - d + 1 + j;
            if(((i >> j) & 1) == 0 && num >= 1 && !fixed[num]) {
                // cout << "not empty: " << i << " j: " << j << '\n';
                empty = true;
            }
        }
        if(!empty) {
            // cout << "ans at: " << i << " score: " << dp[n][i] << '\n';
            ans += dp[n][i];
        }
    }

    cout << ans << '\n';

    return 0;
}