#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
had to think about this one for a while. 
here were the steps taken to solve

visually draw out what is happening. how there are 4 squares in each of the corners
there is a distance between adjacent squares, and we can count the total number of ways to do this, but we should uncount the times where the squares 
touch diagonally. 
This is the main problem of the problem. 

We considered some PIE approaches
We also considered some approaches where we fix how far up the bottom left triangle goes and how far down the upper-right triangle goes and also tried fixing other various things

eventually, we tried fixing the corners between the bottom left and upper right squares. by doing so, we are left with a rectangle where the opposite corners could touch. 
Given that the rectangle dimensions are l x w, there are l * (l + 1) / 2 * w * (w + 1) / 2 placements of the other two squares that will result in a collision. 
Additionally, if the rectangle dimension is l, then there are W - N * 2 - l ways where we can shift these rectangles around. This is the same for the other direction. 

We get a double summation that can be simplified. A nice thing about this double summation is that the l and w variables are independent, and we can easily find a closed formula for both. 

With this, we can count how many times the corners will collide, we should multiply by 2 in order to handle the other corners. 

Not too much combo knowledge needed here, which is why I was able to solve. 

*/

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

void solve() {
    
    ll n, h, w; cin >> n >> h >> w;

    if(n * 2 > h || n * 2 > w) {
        cout << "0\n";
        return;
    }

    auto triangle = [&](Z a) -> Z {
        return a * (a + 1) / 2;
    };

    auto square = [&](Z a) -> Z {
        return a * (a + 1) * (2 * a + 1) / 6;
    };

    auto cube = [&](Z a) -> Z {
        return a * a * (a + 1) * (a + 1) / 4;
    };

    auto get = [&](ll a) -> Z {
        Z za = Z(a);
        Z one = za * triangle(za);
        Z two = (za - 1) * square(za);
        Z three = -1 * cube(za);
        return (one + two + three) / 2;
    };

    ll a = h - n * 2 + 1, b = w - n * 2 + 1;

    // cout << "a : " << a << " b : " << b << '\n';

    Z total_ways = triangle(a) * triangle(a) * triangle(b) * triangle(b);
    Z get_a = get(a), get_b = get(b);

    // cout << "total ways : " << total_ways << '\n';
    // cout << " get a : " << get_a << " get b : " << get_b << '\n';

    cout << total_ways - get_a * get_b * 2 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}