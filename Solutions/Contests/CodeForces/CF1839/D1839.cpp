#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//FF 2100's are too tough
//editorial for this

/*

I got that you needed dp to solve as well as the correct states, couldn't find optimization to make transitions work because didn't know which element after doing ball operations we would stop
adding to our LIS. 

dp[i][j]
i - how many balls have been used
j - the last satisfied index satisfied 
store => min ops

When we do some operations, we have to make sure that the next element is always satisfied

We do not have to take any particular element after it that is satisfied. If a[i] < a[k], we go to index k, but we don't need to go to index k + 1 even if dp[k] < dp[k+1]
We use dp to do that later ...

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

// T1 most creative ways to do likely unintended dp solutions

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, MOD));
    dp[0][0] = 0;

    for(int balls = 0; balls <= n; balls++) { //how many used, 0-indexed
        for(int lastpos = 0; lastpos <= n; lastpos++) { //1-indexed
            int lastposval = (lastpos == 0 ? 0 : a[lastpos - 1]); //stores the value of index from last LIS
            if(lastpos < n && a[lastpos] > lastposval) {
                dp[balls][lastpos + 1] = min(dp[balls][lastpos + 1], dp[balls][lastpos]);
            }
            if(balls) {
                for(int ops = 1; lastpos + ops <= n; ops++) {
                    int lastposcoveredbyops = lastpos + ops;
                    if(lastposcoveredbyops == n) {
                        dp[balls][lastposcoveredbyops] = min(dp[balls][lastposcoveredbyops], dp[balls - 1][lastpos] + ops); //take min
                    } else if(a[lastposcoveredbyops] > lastposval) {
                        dp[balls][lastposcoveredbyops + 1] = min(dp[balls][lastposcoveredbyops + 1], dp[balls - 1][lastpos] + ops); //take min
                    }
                }
            }
        }
    }

    // cout << "dpfinal\n" << dp;

    int res = dp[0][n];

    for(int i = 1; i <= n; i++) {
        res = min(res, dp[i][n]);
        cout << res << " \n"[i == n];
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}