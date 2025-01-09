/*
also see jiangly's template
https://codeforces.com/contest/1895/submission/231571612
*/
template<class T>
constexpr T power(T a, ll b, T base = 1) {
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            base *= a;
        }
    }
    return base;
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

constexpr int P = 1e9 + 7;
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

template<typename T>
struct Matrix {
    static constexpr T base = 0;
    int r, c;
    vector<vector<T>> mat;
    Matrix(vector<vector<T>> _mat) {
        r = _mat.size();
        c = _mat[0].size();
        mat = _mat;
    }
    constexpr Matrix &operator+=(Matrix rhs) & {
        assert(r == rhs.r && c == rhs.c);
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                mat[i][j] += rhs.mat[i][j];
            }
        }
        return *this;
    }
    constexpr Matrix &operator*=(Matrix rhs) & {
        assert(c == rhs.r);
        vector<vector<T>> res(r,vector<T>(rhs.c));
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < rhs.c; j++) {
                for(int k = 0; k < c; k++) {
                    res[i][j] += mat[i][k] * rhs.mat[k][j];
                }
            }
        }
        c = rhs.c;
        mat = res;
        return *this;
    }
    friend constexpr Matrix operator+(Matrix lhs, Matrix rhs) {
        Matrix res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Matrix operator*(Matrix lhs, Matrix rhs) {
        Matrix res = lhs;
        res *= rhs;
        return res;
    }
};