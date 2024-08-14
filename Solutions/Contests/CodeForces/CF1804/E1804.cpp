#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
possible when there exists a cycle where the set of nodes that are directly reachable from the nodes in the cycle contains every element in n.
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<int> bms(n);
    for(int i = 0; i < n; i++) {
        bms[i] = 1 << i;
    }

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        bms[u] |= 1 << v;
        bms[v] |= 1 << u;
    }

    vector<int> good(1 << n);
    for(int i = 0; i < 1 << n; i++) {
        int bm = 0;
        for(int bit = 0; bit < n; bit++) {
            if(i & (1 << bit)) {
                bm |= bms[bit];
            }
        }
        if(bm == ((1 << n) - 1)) {
            good[i] = 1;
        }
    }

    vector<vector<int>> dp(1 << n, vector<int>(n,-1));

    for(int i = 0; i < n; i++) {
        dp[1 << i][i] = -2;
    }

    for(int bm = 1; bm < 1 << n; bm++) {
        int fs = __builtin_ffs(bm) - 1;
        // cout << "bm : " << bm << " fs : " << fs << endl;
        for(int last = fs; last < n; last++) {
            if(dp[bm][last] != -1) {
                // cout << "bm : " << bm << " last : " << last << " is possible with parent : " << dp[bm][last] << "\n";
                for(int to : adj[last]) {
                    if(to == fs) {
                        if(good[bm]) {  
                            // cerr << "bm : " << bm << " last : " << last << endl;
                            // cout << "goodbm : " << bm << endl;
                            int currbm = bm;
                            int currlast = last;
                            vector<int> res(n,-1);
                            while(__builtin_popcount(currbm) > 1) {
                                // cout << "cbm : " << currbm << " cl : " << currlast << " parent : " << dp[currbm][currlast] << endl;
                                res[currlast] = dp[currbm][currlast];
                                int nextbm = currbm ^ (1 << currlast);
                                int nextlast = dp[currbm][currlast];
                                currbm = nextbm;
                                currlast = nextlast;
                            }

                            res[currlast] = last;
                            for(int i = 0; i < n; i++) {
                                for(int j = 0; j < n; j++) {
                                    if(res[j] == -1) {
                                        for(int c : adj[j]) {
                                            if(res[c] != -1) {
                                                res[j] = c;
                                            }
                                        }
                                    }
                                }
                            }

                            cout << "Yes\n";
                            for(int i = 0; i < n; i++) {
                                int num = (res[i] == i ? (res[i] + 1)  % n : res[i]) + 1;
                                cout << num << " \n"[i == n - 1];
                            }

                            return 0;
                        }
                    } else if(to >= fs) {
                        if((bm & (1 << to)) == 0) {
                            dp[bm | (1 << to)][to] = last;
                        }
                    }
                }
            }
        }
    }

    cout << "No\n";

    return 0;
}