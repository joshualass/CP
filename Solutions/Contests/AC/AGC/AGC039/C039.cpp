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

    int n; cin >> n;
    string s; cin >> s;
    vector<int> a(n);
    Z res = 0;
    for(int i = 0; i < n; i++) {
        res *= 2;
        a[i] = s[i] - '0';
        res += a[i];
    }
    res += 1;
    res *= n * 2;

    auto get_cnt = [&](int l) -> Z {
        vector<int> res(a.begin(), a.begin() + l);
        int b = 0;
        for(int i = 0; i < n; i++) {
            int v = res[i%l] ^ ((i / l) & 1);
            if(a[i] < v) {
                b = 1;
                break;
            } else if(a[i] > v) break;
        }
        if(b) {
            if(count(res.begin(),res.end(),0) == l) return 0;
            for(int i = l - 1; i >= 0; i--) {
                if(res[i]) {
                    res[i] = 0;
                    for(int j = i + 1; j < l; j++) res[j] = 1;
                    break;
                }
            }
        }
        Z ans = 0;
        for(int i = 0; i < l; i++) {
            ans *= 2;
            ans += res[i];
        }
        ans += 1;
        return ans;
    };

    vector<Z> subs(n);
    for(int i = 1; i < n; i++) {
        if(n % (i * 2) == i) {
            subs[i] += get_cnt(i);
            for(int j = 3; j * i < n; j += 2) {
                subs[j*i] -= subs[i];
            }
            res += (2 * i - n * 2) * subs[i];
        }
    }

    cout << res << '\n';

    return 0;
}