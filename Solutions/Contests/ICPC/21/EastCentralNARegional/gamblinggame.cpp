#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct Frac {
    ll num = 0, den = 1;

    void simp() {
        ll gg = gcd(num, den);
        num /= gg;
        den /= gg;
    }

    constexpr Frac &operator+=(Frac rhs) {
        num *= rhs.den;
        rhs.num *= den;
        num += rhs.num;
        den *= rhs.den;
        simp();
        return *this;
    }

    constexpr Frac &operator*=(Frac rhs) {
        num *= rhs.num;
        den *= rhs.den;
        simp();
        return *this;
    }

// friend constexpr Mll operator+(Mll lhs, Mll rhs) {

    friend constexpr Frac operator+(Frac lhs, Frac rhs) {
        Frac res;
        res.den = lhs.den * rhs.den;
        lhs.num *= rhs.den;
        rhs.num *= lhs.den;
        res.num = lhs.num + rhs.num;
        res.simp();
        return res;
    }

    friend constexpr Frac operator*(Frac lhs, Frac rhs) {
        Frac res;
        res.den = lhs.den * rhs.den;
        res.num = lhs.num * rhs.num;
        res.simp();
        return res;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const Frac &a) {
        return os << a.num << "/" << a.den << endl;
    }
    
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll m, n, p; cin >> m >> n >> p;

    vector<vector<Frac>> dp(p+1, vector<Frac>(n+1)); // Frac probability of having i squares covered after j selections
 
    dp[0][0].num = 1;
 
    for (int i = 1; i <= p; ++i) {
        for (int j = 0; j <= n; ++j) {
            // didnt pick in last
            Frac didnt;
            didnt.den = m - i + 1;
            didnt.num = (m - i + 1) - (n - j) * 2;
            // cerr << "didnt : " << didnt.num << " " << didnt.den << endl;
            // cerr << "dp : " << dp[i-1][j].num << " " << dp[i-1][j].den << endl;
            if (j != n) {
                Frac to_add = didnt * dp[i-1][j];
                // cerr << "to_add : " << to_add << endl << endl;
                if (didnt.num > 0 && dp[i-1][j].num > 0) {
                    dp[i][j] += to_add;
                }
            }
            
            
            
            

            // did pick
            Frac did;
            did.den = m - i + 1;
            did.num = (n - j + 1) * 2;
            if (j)
                dp[i][j] += dp[i-1][j-1] * did;
        }
    }

    // cerr << "dp : " << dp[1][0].num << "/" << dp[1][0].den << endl;


    cout << dp[p][n].num << "/" << dp[p][n].den << endl;

    return 0;
}