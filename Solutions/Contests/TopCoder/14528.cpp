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

class Hyperboxes {
public:

    Z compute_intersection_ways(int b, int _n) {
        Z n = _n;
        if(b == 1) {
            return (n - 1) * n / 2;
        } else if(b == 2) {
            // return (n - 1) * power<Z>(n,2) * (n + 1) / 12;
            // return power<Z>(n-1,2) * n * (n + 4) / 12;
            // return n * (power<Z>(n,3) + 2 * power<Z>(n,2) - 4 * n + 1) / 6;
            return n * (power<Z>(n,3) - 4 * n + 3) / 6;
        } else if(b == 3) {
            // return power<Z>(n,2) * (power<Z>(n,4) - 1) / 60;
            return n * (power<Z>(n,5) + power<Z>(n,4) - 5 * power<Z>(n, 3) - 5 * power<Z>(n, 2) + 14 * n - 6) / 20;
        } else if(b == 4) {
            return power<Z>(n,2) * (3 * power<Z>(n,6) + 7 * power<Z>(n,2) - 10) / 840;
        } else if(b == 5) {
            return power<Z>(n,2) * (power<Z>(n,8) + 20 * power<Z>(n,2) - 21) / 1260;
        } else if(b == 6) {
            return power<Z>(n,2) * (power<Z>(n,10) - 22 * power<Z>(n,4) + 231 * power<Z>(n,2) - 210) / 5544;
        }
        assert(0);
    }
// (i*(n-i+1)-1)
    int findCount(int n, int m, int k) {

        vector<Z> pc(m + 1, 1);
        for(int i = 1; i <= m; i++) pc[i] = power<Z>(compute_intersection_ways(i, n), k);

        Z res = 0;

        vector<array<int,2>> bad_props;
        for(int i = 0; i < m; i++) {
            for(int j = i + 1; j < m; j++) {
                bad_props.push_back({i,j});
            }
        }

        int edges = bad_props.size();

        for(int bm = 0; bm < 1 << edges; bm++) {
            vector<int> vis(m);
            vector<vector<int>> adj(m);
            for(int i = 0; i < edges; i++) {
                if((bm >> i) & 1) {
                    auto [a, b] = bad_props[i];
                    adj[a].push_back(b);
                    adj[b].push_back(a);
                }
            }

            Z ways = 1;

            for(int i = 0; i < m; i++) {
                int sz = 0;
                queue<int> q;
                q.push(i);
                while(q.size()) {
                    int t = q.front();
                    q.pop();
                    if(vis[t]) continue;
                    vis[t] = 1;
                    sz++;
                    for(int to : adj[t]) q.push(to);
                }
                ways *= pc[sz];
            }

            cout << "bm : " << bm << " ways : " << ways << '\n';

            if(bm & 1) {
                res -= ways;
            } else {
                res += ways;
            }

        }

        return res.x;

        // Z res = power<Z>(compute_intersection_ways(1, n), k * m);

        // cout << "start res : " << res.x << '\n';

        // for(int i = 0; i < 1 << m; i++) {
        //     int pc = __builtin_popcount(i);
        //     if(pc >= 2) {
        //         Z a = power<Z>(compute_intersection_ways(pc,n), k);
        //         Z b = power<Z>(compute_intersection_ways(1,n), k * (m - pc));
        //         Z ways = a * b;
        //         cout << "pc : " << pc << " a : " << a << " b : " << b << " ways : " << ways << '\n';
        //         if(pc & 1) {
        //             res += ways;
        //         } else {
        //             res -= ways;
        //         }
        //     }
        // }

        // return res.x;

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
  auto c = Hyperboxes();
  int ret = c.findCount(arg0, arg1, arg2);
  cout << ret;
}