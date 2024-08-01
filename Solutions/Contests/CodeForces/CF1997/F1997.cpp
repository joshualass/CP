#include <bits/stdc++.h>
typedef long double ld;
using namespace std;
const int MOD = 998244353;

/*
To observe how to find our solution, we will take the starting positions of intial configuration and keep repeating the first option until all elements are on first / second positions.
Then, we see what the final positions will be and we see that each position will cost fib(i) balls to reach the current position. 
Additionally, no final bitmask of positions will have adjacent set bits because we can just do an operation and number of balls decrease.
We precompute for a given max distance of initial balls, for number of balls used, and current count of balls, the number of ways to configure this
We use dp to precompute all these values and use it as a lookup table for when we find valid score from bitmask. 

Could optimize the dp, by having 2 dimensional memory, instead of having to look at old values
Could optimize bm, by precompute the final values for fibonacci numbers in max fib idx * max possible value. 
*/

int fib[30];
int ways[2][1001][55001]; //for given x, what is number of ways to make sum ? [pos][coins][score]

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    fib[0] = 1;
    fib[1] = 1;
    for(int i = 2; i < 30; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    int n, X, m; cin >> n >> X >> m;
    int res = 0;

    for(int x = 0; x < X; x++) {
        int v = fib[x];
        for(int coins = 0; coins <= 1000; coins++) {
            for(int score = 0; score <= 55000; score++) {
                if(x == 0) {
                    ways[x & 1][coins][score] = coins == score;
                } else {
                    ways[x & 1][coins][score] = ways[(x - 1) & 1][coins][score];
                    if(coins && score >= v) {
                        ways[x & 1][coins][score] = ways[x & 1][coins][score] + ways[x & 1][coins - 1][score - v];
                        if(ways[x & 1][coins][score] >= MOD) {
                            ways[x & 1][coins][score] -= MOD;
                        }
                    }
                }
            }
        }
    }

    for(int bm = 0; bm < 1 << 23; bm++) {
        bool ok = __builtin_popcount(bm) == m;
        int needed = 0;
        for(int bit = 0; bit < 23; bit++) {
            if((bm & (1 << bit))) {
                needed += fib[bit + 1];
                if((bm & (1 << (bit + 1)))) {
                    ok = 0;
                }
            }
        }

        if(ok && needed <= 55000) {
            // cout << "needed : " << needed << " add : " << ways[(X - 1) & 1][n][needed] << '\n';
            res = res + ways[(X - 1) & 1][n][needed];
            if(res >= MOD) {
                res -= MOD;
            }
        }
    }

    cout << res << '\n';

    return 0;
}