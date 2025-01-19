#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

vector<Z> fact(1,1);
vector<Z> inv_fact(1,1);

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    while(fact.size() < n + 1) {
        fact.push_back(fact.back() * fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int n; cin >> n;
    // for(int i = 0; i < 1 << n; i++) {
    //     string s = "";
    //     for(int j = 0; j < n; j++) {
    //         if((i >> j) & 1) {
    //             s.push_back('1');
    //         } else {
    //             s.push_back('0');
    //         }
    //     }
    //     string start = s;
    //     for(int j = 0; j < n * 2; j++) {
    //         cout << s << " -> ";
    //         int last = s.back() - '0';
    //         char toggled = (last ^ 1) + '0';
    //         s.pop_back();
    //         s.insert(s.begin(), toggled);
    //         if(s == start) break;
    //     }
    //     cout << s << '\n';
    // }

    // array<int,2> best = {-1,-1};
    // for(int i = 0; i < 200000; i++) {
    //     int cnt = 0;
    //     for(int j = 1; j * 3 <= i; j++) {
    //         if(i % (j * 2) == j) cnt++;
    //     }
    //     if(cnt > best[0]) {
    //         best = {cnt,i};
    //     }
    // }

    // cout << best[0] << ", " << best[1] << '\n';

    int n; cin >> n;
    string s; cin >> s;

    auto get_cnt = [&](int l) -> Z {
        
        vector<int> res(l);
        int p = 0;
        for(int i = 0; i < l; i++) {
            
        }
    };

    return 0;
}

/*
       110011110
      111001111
     011100111
    001110011
   000111001
  000011100
 100001110
110000111
*/