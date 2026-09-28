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
// using Z = double;
const int MAXN = 1e6;
Z fact[MAXN + 1], inv_fact[MAXN + 1];

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

Z choose_slow(ll n, ll k) {
    if(n < 0 || k < 0 || k > n) return 0;
    Z res = 1;
    for(int i = 1; i <= k; i++) {
        res *= n - (i - 1);
        res /= i;
    }
    return res;
}

// void solve() {
    
//     int h, w, k; cin >> h >> w >> k;

//     cout << "h : " << h << " w : " << w << " k : " << k << '\n';

//     ll total_walls = 1LL * (h - 1) * (w - 1);
//     ll total_walls_left = total_walls - ((h - 1) + (w - 1));

//     Z path_combs = choose(h - 1 + w - 1, h - 1);

//     Z single_path_combs = choose(h - 2 + w - 2 + 1, 1) * choose(h - 2 + w - 2, h - 2);

//     Z double_path_combs = choose(h - 3 + w - 3 + 2, 2) * choose(h - 3 + w - 3, h - 3);
//     Z double_tall_combs = choose(h - 3 + w - 2 + 1, 1) * choose(h - 3 + w - 2, h - 3);
//     Z double_short_combs = choose(h - 2 + w - 3 + 1, 1) * choose(h - 2 + w - 3, w - 3);
//     Z double_total_combs = double_path_combs + double_tall_combs + double_short_combs;

//     cout << "zp : " << path_combs << " op : " << single_path_combs << " tp : " << double_tall_combs << '\n';

//     if(k == h + w - 2) {
//         cout << path_combs << '\n';
//     } else if(k == h + w - 1) {

//         cout << "TODO\n";

//     } else if(k == h + w) {

//         Z zero_bad_ways = path_combs * choose_slow(total_walls_left, 2);
//         Z one_bad_ways = single_path_combs * choose_slow(total_walls_left - 1, 1);
//         Z two_bad_ways = double_total_combs * choose_slow(total_walls_left - 2, 0);

//         cout << "zb : " << zero_bad_ways << " ob : " << one_bad_ways << " tb : " << two_bad_ways << '\n';

//         cout << zero_bad_ways - one_bad_ways + two_bad_ways << '\n';

//     } else {
//         cout << "0\n";
//     }

// }

// void solve() {
//     ll h, w, k; cin >> h >> w >> k;

//     cout << "h : " << h << " w : " << w << " k : " << k << '\n';

//     ll total_walls = 1LL * h * (w - 1) + 1LL * (h - 1) * w;
//     ll total_walls_left = total_walls - ((h - 1) + (w - 1));

//     Z path_combs = choose(h - 1 + w - 1, h - 1);


//     Z double_path_combs = choose(h - 2 + w - 2 + 1, 1) * choose(h - 2 + w - 2, h - 2);

//     cout << "tw : " << total_walls << " twl : " << total_walls_left << " pc : " << path_combs << " dc : " << double_path_combs << '\n';

//     if(k == w + h - 2) {
//         cout << path_combs << '\n';
//     } else if(k == w + h - 1) {
//         cout << path_combs * choose_slow(total_walls_left, 1) << '\n';
//     } else if(k == w + h) {
//         cout << path_combs * choose_slow(total_walls_left, 2) - double_path_combs * choose_slow(total_walls_left - 2, 0) << '\n';
//     } else {
//         cout << "0\n";
//     }

// }

// void solve() {
//     ll h, w, k; cin >> h >> w >> k;

//     cout << "h : " << h << " w : " << w << " k : " << k << '\n';

//     ll total_walls = 1LL * h * (w - 1) + 1LL * (h - 1) * w;
//     ll total_walls_left = total_walls - ((h - 1) + (w - 1));

//     Z path_combs = choose(h - 1 + w - 1, h - 1);

//     Z double_path_combs = choose(h - 2 + w - 2 + 1, 1) * choose(h - 2 + w - 2, h - 2);

//     cout << "tw : " << total_walls << " twl : " << total_walls_left << " pc : " << path_combs << " dc : " << double_path_combs << '\n';

//     if(k == w + h - 2) {
//         cout << path_combs << '\n';
//     } else if(k == w + h - 1) {
//         cout << path_combs * choose_slow(total_walls_left, 1) << '\n';
//     } else if(k == w + h) {
//         cout << path_combs * choose_slow(total_walls_left, 2) - double_path_combs << '\n';
//     } else {
//         cout << "0\n";
//     }

// }

void solve() {
    ll h, w, k; cin >> h >> w >> k;
    ll tl = h * (w - 1) + (h - 1) * w;

    if(k == h + w) {

        auto get_zig = [](ll h, ll w) -> Z {
            if(w < 3) return 0;
            Z total = choose(h + w - 3 + 1, h) * choose(w - 3 + 1, w - 3);
            Z bad_cnt = choose(h + w - 3 + 1, h + 1) * 2;
            return total - bad_cnt;
        };
        Z base = choose(h - 1 + w - 1, h - 1) * choose_slow(tl - (h - 1 + w - 1), 2);
        Z dup = choose(h - 2 + w - 2 + 1, 1) * choose(h - 2 + w - 2, h - 2);
        Z z1 = get_zig(h, w), z2 = get_zig(w, h);

        // cout << "base : " << base << " dup : " << dup << " z1 : " << z1 << " z2 : " << z2 << '\n';
        
        cout << base - dup + z1 + z2 << '\n';
    } else if(k == h + w - 1) {
        cout << choose(h - 1 + w - 1, h - 1) * choose_slow(tl - (h - 1 + w - 1), 1) << '\n';
    } else if(k == h + w - 2) {
        cout << choose(h - 1 + w - 1, h - 1) << '\n';
    } else {
        cout << "0\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}