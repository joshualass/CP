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

constexpr int P = 998244353;
using Z = Mint<P>;

class LongSeat {
public:
    Z compute_intersection_ways(int b, int _n) {
        Z n = _n;
        if(b == 1) {
            return (n - 1) * n / 2;
        } else if(b == 2) {
            return (n - 1) * power<Z>(n,2) * (n + 1) / 12;
        } else if(b == 3) {
            return power<Z>(n,2) * (power<Z>(n,4) - 1) / 60;
        } else if(b == 4) {
            return power<Z>(n,2) * (3 * power<Z>(n,6) + 7 * power<Z>(n,2) - 10) / 840;
        } else if(b == 5) {
            power<Z>(n,2) * (power<Z>(n,8) + 20 * power<Z>(n,2) - 21) / 1260;
        } else if(b == 6) {
            return power<Z>(n,2) * (power<Z>(n,10) - 22 * power<Z>(n,4) + 231 * power<Z>(n,2) - 210) / 5544;
        }
        assert(0);
    }

    vector<string> canSit(int L, vector<int> width) {
        


        vector<string> res;
        for(int i = 0; i < width.size(); i++) {


            


        }
    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int n1; cin >> n1;
  vector<int> arg1(n1);
  for (int i=0;i<n1;++i) { cin >> arg1[i]; }
  auto c = LongSeat();
  vector<string> ret = c.canSit(arg0, arg1);
  for (auto& item : ret) { cout << item << "\n"; }
}