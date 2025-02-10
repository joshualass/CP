#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
good combinatorics practice :o

First, need to observe what subsequences are and are not possible. It is possible if there exists an unremoved element in the sequence that has at least k removed elements to left and right. 
Approaches (a lot) considered:
for each k and each number of operations, we can count the number of bad subsequences if L is the k'th removed element from the left and R is the k'th removed element, then if R - L equiv 1 mod 2k, then that is a bad
subsequence. This results in a nasty double summation. 
Alternatively, consider the good subsequences. Let G be the leftmost element after at least k removed elements, for each G, we count the number of ways to place >= k elements on left and right such that they divide 2k. 
I was able to get a nasty triple summation here. 
It didn't seem like the summing approaches were helpful, so had to try something else. Tried something like inclusion exclusion where if there are x ways to get to this current state, what are the # of ways to get to the next state?
but for some states there are more or less ways to make than others.

Finally, tried to compute the number of ways to make the first operation. We have that there are n choose 2k number of subsets, but the subsets that are bad have the k'th and k+1'th element adjacent to each other. 
We can create a bijective mapping to n - 1 choose 2k - 1 where for the k'th element, we add a removed element before for the mapping. We observe that we can do this same trick for more operations. 
There are n choose 2kj number of ways to do j operations for given k. The bad ones are the maps with n - 2kj - 1 choose 2k - 1... :)
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

void solve() {
    int n; cin >> n;
    for(int k = 1; k <= (n - 1) / 2; k++) {
        int t = n;
        Z res = 1;
        // cout << "k : " << k << " start : " << res << '\n';
        while(t > k * 2) {
            res += choose(n,t-k*2);
            res -= choose(t-1,2*k-1);
            t -= k * 2;
        }
        cout << res << " \n"[k == (n - 1) / 2];
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