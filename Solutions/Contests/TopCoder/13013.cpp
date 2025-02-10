#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;

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

constexpr int P = 1e9+7;
using Z = Mint<P>;

const int MAX_LENGTH = 1e6;
class CycleColoring {
public:
    int countColorings(vector<int> vertexCount, vector<int> fromVertex, vector<int> toVertex, int K) {
        vector<Z> s(MAX_LENGTH + 1), d(MAX_LENGTH + 1);
        Z k(K);
        s[0] = 1;
        for(int i = 1; i <= MAX_LENGTH; i++) {
            s[i] = d[i-1];
            d[i] = s[i-1] * (k - 1) + d[i-1] * (k - 2);
        }
        Z cs = 1, cd = 0;
        int n = vertexCount.size();
        for(int i = 0; i < n; i++) {
            int vc = vertexCount[i];
            int a = toVertex[(i+n-1)%n], b = fromVertex[i];
            int l1 = abs(a-b);
            int l2 = vc - l1;
            Z ts = s[l1] * s[l2];
            Z td = d[l1] * d[l2] / (k-1);
            Z ns = cs * ts + cd * td / (k-1);
            Z nd = cs * td + cd * (td * (k - 2) / (k - 1) + ts);
            cs = ns;
            cd = nd;
        }
        return (cs * k).x;
    }
};
// SOLUTION_END

int main() {
  int n0; cin >> n0;
  vector<int> arg0(n0);
  for (int i=0;i<n0;++i) { cin >> arg0[i]; }
  int n1; cin >> n1;
  vector<int> arg1(n1);
  for (int i=0;i<n1;++i) { cin >> arg1[i]; }
  int n2; cin >> n2;
  vector<int> arg2(n2);
  for (int i=0;i<n2;++i) { cin >> arg2[i]; }
  int arg3;
  cin >> arg3;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = CycleColoring();
  int ret = c.countColorings(arg0, arg1, arg2, arg3);
  cout << ret;
}