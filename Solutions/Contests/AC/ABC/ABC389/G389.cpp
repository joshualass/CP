#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
current ideas 
have dp state
# nodes
# parity diff
# size of previous layer
# binom count
# next layer

have binom because a lot of the states can be 0/1 

We can optimize the state by noticing all the edges on the same layer is like that of the binomial distribution. for each pair of 
nodes, we can choose to or not choose to have an edge between the pair on the same level. However, this does not work for the edges 
between layers as a node must have some edge, so it's not 0/1 distribution for all of these edges ... don't know how to fix 
and run in time. 

latest idea
add to the next layer one node at a time. 
Maybe these ideas can inspire later ideas. 

This works. 
Took a while to debug. 
annoying to implement without mint lol :(

I think this is O(n^6) ? 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int p;

int power(int a, ll b) {
    int res = 1;
    while(b) {
        if(b & 1) {
            res = 1LL * res * a % p;
        }
        a = 1LL * a * a % p;
        b /= 2;
    }
    return res;
}

int inv(int x) {
    return power(x, p - 2);
}

/*
init_fact()
*/

//# nodes parity / parity offset / number of nodes in previous layer / binom / next layer
int dp[2][31][16][422][16];
int binom_sum[422];
int chooses[1000][1000];
int res[1000];
int fact[40];
int invs[40];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n >> p;

    fact[0] = 1;
    for(int i = 1; i < 40; i++) {
        fact[i] = 1LL * fact[i-1] * i % p;
        invs[i] = inv(i);
    }

    //req 0 <= lhs <= p - 1, -p <= rhs <= p - 1
    auto add = [&](int lhs, int rhs) -> int {
        lhs += rhs;
        if(lhs >= p) lhs -= p;
        if(lhs < 0) lhs += p;
        return lhs;
    };

    dp[1][16][1][0][0] = 1;

    for(int i = 1; i < n; i++) {
        int ci = i & 1;
        int ni = ci ^ 1;
        for(int j = 0; j < 31; j++) {
            for(int k = 0; k < 16; k++) {
                for(int l = 0; l < 422; l++) {
                    for(int m = 0; m < 16; m++) {
                        dp[ni][j][k][l][m] = 0;
                    }
                }
            }
        }

        for(int par = 0; par <= 30; par++) {
            for(int pl = 1; pl <= 15; pl++) {
                for(int binom = 0; binom <= 421; binom++) {
                    for(int nl = 0; nl <= 15; nl++) {
                        if(dp[ci][par][pl][binom][nl]) {
                            // cout << "i : " << i << " par : " << par << " pl : " << pl << " binom : " << binom << " nl : " << nl << '\n';
                            int here = dp[ci][par][pl][binom][nl];
                            // cout << "val : " << here << '\n';
                            //case add to next layer
                            if(par - 1 >= 0 && nl < 15) {
                                // cout << "case add to next layer\n";
                                //ni defined
                                int nxpar = par - 1;
                                //pl is still same
                                int nl_binom_sub = binom + nl;
                                int nl_binom_add = binom + nl + pl;
                                assert(nl_binom_add <= 421);
                                int nxnl = nl + 1;
                                int nxval = 1LL * here * invs[nxnl] % p;
                                // cout << "nxpar : " << nxpar << " nl_binom_sub : " << nl_binom_sub << " nl_binom_add : " << nl_binom_add << " nxnl : " << nxnl << '\n';
                                dp[ni][nxpar][pl][nl_binom_sub][nxnl] = add(dp[ni][nxpar][pl][nl_binom_sub][nxnl], -nxval);
                                dp[ni][nxpar][pl][nl_binom_add][nxnl] = add(dp[ni][nxpar][pl][nl_binom_add][nxnl], nxval);
                            }
                            //case create new layer
                            int nxpar = (30 - par) - 1;
                            if(nxpar >= 0 && nxpar <= 30 && nl) {
                                // cout << "case create next layer\n";
                                //ni defined
                                int npl = nl;
                                int nl_binom_sub = binom;
                                int nl_binom_add = binom + nl;
                                assert(nl_binom_add <= 421);
                                int nxnl = 1;
                                // cout << "nxpar : " << nxpar << " npl : " << npl << " nl_binom_sub : " << nl_binom_sub << " nl_binom_add : " << nl_binom_add << " nxnl : " << nxnl << '\n';
                                dp[ni][nxpar][npl][nl_binom_sub][nxnl] = add(dp[ni][nxpar][npl][nl_binom_sub][nxnl], -here);
                                dp[ni][nxpar][npl][nl_binom_add][nxnl] = add(dp[ni][nxpar][npl][nl_binom_add][nxnl], here);
                            }
                        }
                    }
                }
            }
        }
    }


    int li = n & 1;
    for(int pl = 1; pl < 16; pl++) {
        for(int binom = 0; binom < 422; binom++) {
            for(int nl = 0; nl < 16; nl++) {
                binom_sum[binom] = add(binom_sum[binom], dp[li][15][pl][binom][nl]);
            }
        }
    }

    chooses[0][0] = 1;

    for(int i = 1; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            chooses[i][j] = add(j ? chooses[i-1][j-1] : 0, chooses[i-1][j]);
        }
    }

    for(int i = 0; i < 422; i++) {
        for(int j = 0; j <= i; j++) {
            res[j] = add(res[j], 1LL * chooses[i][j] * binom_sum[i] % p);
        }
    }

    for(int i = n - 1; i <= n * (n - 1) / 2; i++) {
        cout << 1LL * res[i] * fact[n-1] % p << " \n"[i == n * (n - 1) / 2];
    }

    return 0;
}
