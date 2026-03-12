#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

//Modular Division currently uses Little Fermat's Theorem, so won't work for nonprime p. 
template<int P>
struct Mint {
    int x;
    constexpr Mint(): x{} {}
    constexpr Mint(ll x): x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if(P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if(x < 0) {
            x += getMod();
        }
        if(x >= getMod()) { //not sure why this is needed
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    constexpr Mint operator-() const {
        Mint res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr Mint inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr Mint &operator*=(Mint rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr Mint &operator+=(Mint rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr Mint &operator-=(Mint rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr Mint &operator/=(Mint rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr Mint operator*(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Mint operator+(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Mint operator-(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Mint operator/(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
        ll v;
        is >> v;
        a = Mint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(Mint lhs, Mint rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(Mint lhs, Mint rhs) {
        return lhs.val() != rhs.val();
    }
};

constexpr int P = 1e9 + 7;
using Z = Mint<P>;
// using Z = double;
Z p4[5002 * 2 + 1];
Z dp[2][5000][2][2];
Z res[5000][5000];

/*
init_fact()
*/

/*
 1
2X0
 3
*/

void solve() {
    
    int n, m; cin >> n >> m;
    cout << res[n-1][m-1] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    p4[0] = 1;
    for(int i = 1; i <= 5002 * 2; i++) p4[i] = p4[i-1] * 4;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                int x = k == 0, y = j == 3;
                dp[0][0][x][y] += 1;
            }
        }
    }

    for(int i = 0; i < 5000; i++) {
        int curi = i & 1, nxi = (i & 1) ^ 1;
        for(int j = 0; j < 5000; j++) for(int k = 0; k < 2; k++) for(int l = 0; l < 2; l++) dp[nxi][j][k][l] = 0;
        for(int j = 0; j < 5000; j++) {
            for(int k = 0; k < 2; k++) {
                for(int l = 0; l < 2; l++) {
                    for(int nx = 0; nx < 4; nx++) {
                        if(k == 0 && nx != 2) {
                            //go down
                            if(i + 1 < 5000) { //transition down if possible
                                int nxl = nx == 3;
                                dp[nxi][j][0][nxl] += dp[curi][j][k][l] * p4[j] * 3;
                                dp[nxi][j][1][nxl] += dp[curi][j][k][l] * p4[j];
                            }
                        } else if(l == 0 && nx != 1 && (k || nx == 2)) {
                            //go right
                            if(j + 1 < 5000) { //transition right if possible
                                int nxk = nx == 0;
                                dp[curi][j+1][nxk][0] += dp[curi][j][k][l] * p4[i] * 3;
                                dp[curi][j+1][nxk][1] += dp[curi][j][k][l] * p4[i];
                            }
                        } else {
                            //stuck here ~ valid
                            assert((k == 1 || nx == 2) && (l == 1 || nx == 1));
                            res[i][j] += dp[curi][j][k][l];
                        }
                    }
                }
            }
            if(i) res[i][j] += res[i-1][j] * p4[j + 2];
            if(j) res[i][j] += res[i][j-1] * p4[i + 2];
            if(i && j) res[i][j] -= res[i-1][j-1] * p4[i + j + 3];
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}