#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
ll MOD;

/*
insanely high quality problem from this edu round (for me)

reflection
I read this problem and it is quite apparent that it is a matexp problem from constraints and problem type. 
I tried a pretty naive dp state that obviously overcounted - a dp state that only considered where the ball dropped. 
This didn't work, and then I developed a new dp state where dp[i] stores the number of states having the leftmost position be at index i. 
However, when one transitions from a leftmost state to states further left, we should uncount any future states where the right endpoint is less than the left endpoint. 

I spent a very long time trying to do some PIE approaches on this and failed to realize for a long time why it failed - it wasn't correctly uncounting things and was quickly spiralling out 
of control of things that we can and cannot count. 

I also remember trying to approaches where I counted the bad states, which isn't a bad thing to consider. 

My intuition told me that there is some property of these transitions where we might be able to uncount with an existing state or add a state to help with this. 
It was not until I explicitly drew out the range transitions that each dp[i] state trasitions to
dp[i] for j >= i, dp[i] += dp[i] * (m - j) or m - j copies to [j, j - (m - 1)]
      for j < i, add m - i copies to [j, j - (m - 1)]

After drawing this out, it still wasn't obvious what to do. Then, I drew a 2D picture of what these transitions look like on a range. 
I shaded in the region and saw the transitions, and marked the transition type. I then observed that we could have a symmetrical state, storing the right endpoint and 
created a second dp state for the right endpoints and this cleanly solves the problem. 

However, we should further optimize and realize that the r states are symmetrical to the l states!!! because their structures act similarly, so we can have l states transition to themselves in an incredibly clean manner. 
W problem, L long duration of time spent thinking about it :)
*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<vector<ll>> matmult(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    int n = a.size();
    vector<vector<ll>> res(n,vector<ll>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int z = 0; z < n; z++) {
                res[i][j] += a[i][z] * b[z][j];
                res[i][j] %= MOD;
            }
        }
    }
    return res;
}
//use notation of [from][to]
vector<vector<ll>> matexp(vector<vector<ll>> result, vector<vector<ll>> mat, ll pow) {
    int n = mat.size();
    while(pow) {
        if(pow & 1) {
            result = matmult(result,mat); //result is the current matrix, mat is the binexp matrix
        }
        mat = matmult(mat,mat);
        pow >>= 1;
    }
    return result;
}

int debug = 0;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m >> MOD;
    // vector<vector<ll>> base(m * 2 + 2, vector<ll>(m * 2 + 2)), mat(m * 2 + 2, vector<ll>(m * 2 + 2));
    // base[0][0] = 1;

    // for(int i = 0; i < m; i++) {
    //     //normal transitions
    //     for(int j = 0; j < m; j++) {
    //         ll mult = (m - max(i,j)) % MOD;
    //         mat[i][j] = mult;
    //         for(int k = j; k < i; k++) {
    //             ll multmult = mult * (m - k) % MOD;
    //             mat[i][k+m] = ((-multmult + mat[i][k+m]) % MOD + MOD) % MOD;
    //         }
    //         // cout << "i : " << i << " j : " << j << " mult : " << mult << endl;
    //         mat[i][m * 2 + 1] = (((-mult * max(0, i - j) + mat[i][m * 2 + 1]) % MOD) + MOD) % MOD;
    //     }
    //     //contribution to res
    //     mat[i][m * 2] = (m - i);
    // }

    // //go up a step
    // for(int i = 0; i < m; i++) {
    //     mat[i + m][i] = 1;
    // }
    // mat[m * 2 + 1][m * 2] = 1;

    // //answer is cumulative
    // mat[m * 2][m * 2] = 1;

    // cout << "mat begin" << endl;
    // for(auto x : mat) cout << x << endl;

    // auto res = matexp(base, mat, n);

    // cout << "res" << endl;
    // for(auto x : res) cout << x << endl;

    // cout << res[0][m * 2] << '\n';

    // vector<vector<ll>>base(m * 2 + 1, vector<ll>(m * 2 + 1)), mat(m * 2 + 1, vector<ll>(m * 2 + 1));

    // base[0][0] = 1;
    // for(int i = 0; i < m; i++) {
    //     for(int j = 0; j < m; j++) {
    //         mat[i][j] = (m - max(i,j)) % MOD;
    //         if(j < i) {
    //             mat[i][j+m] = ((i - m) % MOD + MOD) % MOD;
    //         }
    //     }
    //     mat[i][m * 2] = (m - i) % MOD;
    // }

    // for(int i = 0; i < m; i++) {
    //     for(int j = 0; j < m; j++) {
    //         mat[i+m][j+m] = (min(i,j) + 1) % MOD;
    //         if(j > i) {
    //             mat[i+m][j] = (-(i+1) % MOD + MOD) % MOD;
    //         }
    //     }
    //     mat[i+m][m*2] = (i + 1) % MOD;
    // }
    // mat[m*2][m*2] = 1;

    // auto res = matexp(base, mat, n);
    // cout << res[0][m*2] << '\n';

    vector<vector<ll>>base(m + 1, vector<ll>(m + 1)), mat(m + 1, vector<ll>(m + 1));

    base[0][0] = 1;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            mat[i][j] = (m - max(i,j) + mat[i][j]) % MOD;
            if(j < i) {
                mat[i][m-j-1] = ((i - m + mat[i][m-j-1]) % MOD + MOD) % MOD;
            }
        }
        mat[i][m] = (m - i) % MOD;
    }

    mat[m][m] = 1;

    auto res = matexp(base, mat, n);
    cout << res[0][m] << '\n';

    if(debug) {
        vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(m, vector<ll>(m)));
        for(int i = 0; i < m; i++) dp[0][0][i] = 1;
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < m; j++) {
                for(int k = j; k < m; k++) {
                    for(int l = 0; l <= k; l++) {
                        for(int r = max(l, j); r < m; r++) {
                            dp[i][j][k] += dp[i-1][l][r];
                        }
                    }
                }
            }
        }
        ll res = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < m; k++) {
                    res += dp[i][j][k];
                }
            }
        }
        cout << "solve slow solution : " << res << '\n';

        // cout << "expected last row" << endl;
        // for(int i = 0; i < m; i++) {
        //     ll s = 0;
        //     for(int j = i; j < m; j++) {
        //         s += dp[n-1][i][j];
        //     }
        //     cout << s << " ";
        // }
        // cout << endl;

        // auto res2 = matexp(base, mat, n - 1);
        // cout << "one less res" << endl;
        // for(int i = 0; i < m * 2 + 2; i++) {
        //     if(i < m) res2[0][i] *= (m - i);
        //     cout << res2[0][i] << " ";
        // }
        // cout << endl;
        
        // cout << "entire res2" << endl;
        // for(auto x : res2) cout << x << endl;
    }

    return 0;
}
