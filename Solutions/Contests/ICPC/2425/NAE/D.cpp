#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;

struct Frac {
    ll num = 0, den = 1;

    void reduce() {
        ll gg = gcd(num, den);
        num /= gg;
        den /= gg;
    }

    void add(Frac other) {
        num *= other.den;
        other.num *= den;
        den *= other.den;
        num += other.num;
        reduce();
    }

    void multiply(Frac other) {
        num *= other.num;
        den *= other.den;
        reduce();
    }

    void repr() {
        cout << num << "/" << den << endl;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll _n, _d, _x, _y;
    cin >> _n >> _x >> _y >> _d;
    lll n = _n, x = _x, y = _y, d = _d;

    vector dp(d+1, vector(n+1, vector<lll>(n+1, 0)));
    // vector<vector<vector<lll>>> dp;

    dp[0][x][y] = 1;

    auto get_left = [&](int k) -> int {
        if (k == 1)
            return k;
        return k-1;
    };
    // cerr << "hey" << endl;

    auto get_right = [&](int k) -> int {
        if (k == n)
            return k;
        return k+1;
    };

    for (int i = 1; i <= d; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                if (j == k)
                    continue;
                
                for (int ii = 0; ii < 2; ++ii) {
                    for (int jj = 0; jj < 2; ++jj) {
                        int fi, se;
                        if (!ii)
                            fi = get_left(j);
                        else
                            fi = get_right(j);
                        if (!jj)
                            se = get_left(k);
                        else
                            se = get_right(k);
                        // comes from (fi, se)
                        dp[i][j][k] += dp[i-1][fi][se];
                    }
                }
                
            }
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         if (i == j)
    //             continue;
    //         cerr << "i : " << i << " j : " << j << " dp : " << dp[2][i][j] << endl;
    //     }
    // }

    lll cnt = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j)
                continue;
            cnt += dp[d][i][j];
        }
    }



    lll den = 1;
    for (int i = 1; i <= d; ++i) {
        den *= (lll)4;
    }

    cnt = den - cnt;
    // cerr << "den : " << den << endl;
    // cerr << "cnt : " << cnt << endl;


    lll gg = gcd(den, cnt);

    den /= gg;
    cnt /= gg;

    cout << (ll) cnt << "/" << (ll) den << endl;

    return 0;
}

/*
dmot answer
4611685987694141149/4611686018427387904

3695373947956092637/4611686018427387904

*/