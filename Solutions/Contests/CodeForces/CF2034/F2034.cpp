#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//FF MISREAD-FORCES. ez pz ev problem. 

/*
first, we can try to calculate the probability from starting from a cell to ending to another cell. 
can work out a few examples by hand to see the pattern. 
I got (r+s)!/(r!s!) * (n+m-r_s)!/(n+m)! * n!/(n-r)! * m!/(m-s)!

Second, need to find a way to count the doubles. 
What we can observe by induction. If we include points one at a time in some sorted order, let's try to find their effect on the outcome.
we see that the double operation is similar to adding the probability score from this cell to the rest of the cells. 
We can do a dp state of this to count the scores at each cell, so we can count ho wmuch they double. We only need calculate the scoring resulting up
to each point. 
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

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

constexpr int P = 998244353;
using Z = Mint<P>;
const int MAXN = 1e6 + 1;

Z facts[MAXN];
Z ifacts[MAXN];

void solve() {
    int n, m, k; cin >> n >> m >> k;

    vector<array<int,2>> a(k);
    vector<Z> s(k);

    for(int i = 0; i < k; i++) {
        int r, b; cin >> r >> b;
        a[i] = {n-r, m-b};
    }

    auto getp = [&](int sr, int sb, int er, int eb) -> Z {
        if(er < sr || eb < sb) return 0;
        int R = er - sr;
        int B = eb - sb;
        int N = n - sr;
        int M = m - sb;
        Z res = facts[R+B] * ifacts[R] * ifacts[B] * facts[N+M-R-B] * ifacts[N+M] * facts[N] * ifacts[N-R] * facts[M] * ifacts[M-B];
        // cout << "sr : " << sr << " sb : " << sb << " er : " << er << " eb : " << eb << " res : " << res << '\n';
        return res;
    };

    Z res = n * 2 + m;

    sort(a.begin(), a.end());

    for(int i = 0; i < k; i++) {
        // cout << "i : " << i << " a[i] : " << a[i] << '\n';
        s[i] += getp(0,0,a[i][0],a[i][1]) * (2 * a[i][0] + a[i][1]);
    }

    for(int i = 0; i < k; i++) {
        res += s[i];
        for(int j = i + 1; j < k; j++) {
            s[j] += getp(a[i][0], a[i][1], a[j][0], a[j][1]) * s[i];
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    facts[0] = 1;
    ifacts[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        facts[i] = facts[i-1] * i;
        ifacts[i] = 1 / facts[i];
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}