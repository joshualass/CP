#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;

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
const int MAXN = 1e6 + 1;
vector<Z> fact(MAXN), inv_fact(MAXN), res(MAXN), pows(MAXN);

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

void init_fact(int n = MAXN) {
    fact[0] = Z(1);
    inv_fact[0] = Z(1);
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i;
    }
    inv_fact[n] = 1 / fact[n];
    for(int i = n - 1; i >= 1; i--) {
        inv_fact[i] = inv_fact[i+1] * (i + 1);
    }
}

/*
init_fact()
*/

class PBG {
public:
    int findEV(int P, int B, int G) {

        Z p = P, b = B, g = G;

        vector<Z> inv(P + B + G + 1);
        for(int i = 1; i <= P + B + G; i++) {
            inv[i] = Z(1) / i;
        }

        vector<vector<Z>> expected_brown_path(G + P + 1, vector<Z>(B + 1));
        vector<Z> expected_brown(G + P + 1);

        expected_brown_path[G + P][B] = 1;

        for(int i = P + G; i >= 0; i--) {
            for(int j = B; j >= 0; j--) {
                if(i == 0 && j == 0) continue;
                Z GP_fight = Z(i) * inv[i + j] * Z(i - 1) * inv[i + j - 1];
                Z B_fight = 1 - GP_fight;
                expected_brown[i] += expected_brown_path[i][j] * GP_fight * j;
                if(i) {
                    expected_brown_path[i - 1][j] += expected_brown_path[i][j] * GP_fight;
                }
                if(j) {
                    expected_brown_path[i][j - 1] += expected_brown_path[i][j] * B_fight;
                }
            }
        }

        vector<vector<Z>> la(G + 1, vector<Z>(P + 1));
        la[G][P] = 1;

        Z res = 0;

        for(int i = G; i >= 0; i--) {
            for(int j = P; j >= 0; j--) {
                if(i == 0 && j == 0) continue;
                Z limak_dies = (Z(i) + Z(j - 1) * inv[2]) * inv[i + j] * inv[i + j - 1] * 2;
                Z G_dies = Z(i) * Z(i - 1) * inv[i + j] * inv[i + j - 1];
                Z P_dies = 1 - limak_dies - G_dies; //not Limak
                Z expected_brown_alive = expected_brown[i + j];

                Z d = (i == 0 && j == 1 ? la[i][j] : (expected_brown_alive + i + j) * la[i][j] * limak_dies);

                res += d;

                if(i) {
                    la[i-1][j] += la[i][j] * G_dies;
                }

                if(j) {
                    la[i][j-1] += la[i][j] * P_dies;
                }

            }   
        }

        return res.x;

    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg1;
  cin >> arg1;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg2;
  cin >> arg2;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = PBG();
  int ret = c.findEV(arg0, arg1, arg2);
  cout << ret;
}