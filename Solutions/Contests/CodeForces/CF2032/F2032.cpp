#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
nice nim game + counting problem
took a lot of time to solve :'(

Case that wasn't considered
When we considered all the consecutive 1's, we should not consider the bad state. 

Idea
For the last box, winning = xor of values != 0
For the other box, you want to go last, so you can go first on the next box and control
If all 1's, then it's forced alternation
If not, then we check the xor of all the values, then, player 1 can force to either go last or second to last iff the xor of all the numbers != 0.
Then, we do dp on the bad values, and make sure not to count the bad values

slow 2700 slice

*/

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
    friend constexpr bool operator<(Mint lhs, Mint rhs) {
        return lhs.val() < rhs.val();
    }
};

constexpr int P = 998244353;
using Z = Mint<P>;

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    map<Z,Z> bad;
    vector<array<Z,2>> dp(n);
    vector<array<Z,2>> toadd;
    array<Z,2> ps = {0,1};
    int r = n;
    ll c = 0;

    for(int i = n - 1; i >= 0; i--) {
        c ^= a[i];
        if(a[i] == 1) {
            dp[i] = {ps[1],ps[0]};
            if(r != n) {
                Z left = power(Z(2), n-1-r);
                Z t = bad[c] + (c == 0);
                dp[i][0] += left - t;
                dp[i][1] += t;
            }
        } else {
            while(toadd.size()) {
                array<Z,2> b = toadd.back();
                bad[b[0]] += b[1];
                toadd.pop_back();
            }
            Z left = power(Z(2),n-1-i);
            Z t = bad[c] + (c == 0);
            dp[i][0] = left - t;
            dp[i][1] = t;
            ps = {0,0};
            r = i;
        }
        toadd.push_back({c,power(Z(2),n-1-i)});
        swap(ps[0],ps[1]);
        ps[0] += dp[i][0];
        ps[1] += dp[i][1];
    }

    // cout << "dp\n";
    // for(auto x : dp) cout << x << '\n';

    cout << dp[0][0] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}