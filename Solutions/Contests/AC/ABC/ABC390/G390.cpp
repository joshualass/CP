#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
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

void fft(vector<complex<double>>& a) {
    int n = a.size(), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<complex<double>> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i = k; i < 2 * k; i++) 
            rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vector<int> rev(n);
    for (int i = 0; i < n; i++) 
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i = 0; i < n; i++) 
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) 
        for (int i = 0; i < n; i += 2 * k) 
            for (int j = 0; j < k; j++) {
                // complex<double> z = rt[j + k] * a[i + j + k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];  /// exclude-line
                complex<double> z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}

vector<double> conv(const vector<double>& a, const vector<double>& b) {
    if (a.empty() || b.empty()) return {};
    vector<double> res(a.size() + b.size() - 1);
    int L = 32 - __builtin_clz(res.size()), n = 1 << L;
    vector<complex<double>> in(n), out(n);
    copy(a.begin(), a.end(), in.begin());
    for (int i = 0; i < b.size(); i++) 
        in[i].imag(b[i]);
    fft(in);
    for (complex<double>& x : in) 
        x *= x;
    for (int i = 0; i < n; i++) 
        out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    for (int i = 0; i < res.size(); i++) 
        res[i] = imag(out[i]) / (4 * n);
    return res;
}

template<int M> vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> res(a.size() + b.size() - 1);
    int B = 32 - __builtin_clz(res.size()), n = 1 << B, cut = int(sqrt(M));
    vector<complex<double>> L(n), R(n), outs(n), outl(n);
    for (int i = 0; i < a.size(); i++) 
        L[i] = complex<double>((int)a[i] / cut, (int)a[i] % cut);
    for (int i = 0; i < b.size(); i++) 
        R[i] = complex<double>((int)b[i] / cut, (int)b[i] % cut);
    fft(L), fft(R);
    for (int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    for (int i = 0; i < res.size(); i++) {
        ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
        ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    vector<int> p10;
    p10.push_back(1);
    while(p10.size() != 8) p10.push_back(p10.back() * 10);

    int n; cin >> n;

    auto work = [&](vector<int> lens) -> Z {
        int sum_len = accumulate(lens.begin(), lens.end(), 0);
        vector dp(lens.size() + 1, vector<Z>(sum_len + 1));
        dp[0][0] = 1;
        for(int i = 0; i < lens.size(); i++) {
            Z c = 0, sub_mult = power(Z(p10[i+1]), lens[i]);
            vector<ll> a(dp[i].size()), b;
            for(int j = 0; j < dp[i].size(); j++) {
                a[j] = dp[i][j].x;
            }
            b.push_back(1);
            for(int j = 1; j <= lens[i]; j++) {
                b.push_back(Z(choose(lens[i],j) * power(Z(p10[i+1]),j)).x);
            }
            // cout << "a : " << a << " b : " << b << '\n';
            vector<ll> res = convMod<P>(a, b);
            for(int j = 0; j <= sum_len; j++) {
                dp[i+1][j] = res[j];
            }
        }

        // for(int i = 0; i <= lens.size(); i++) cout << "i : " << i << " dp[i] : " << dp[i] << '\n';
        Z res = 0;
        for(int i = 0; i <= sum_len; i++) {
            res += dp[lens.size()][i] * fact[sum_len - i] * fact[i];
        }
        // cout << "lens : " << lens << " res : " << res << '\n';
        return res;
    };

    vector<int> lens;
    vector<Z> sums;
    for(int i = 0; i < 6; i++) {
        int lo = p10[i], hi = min(n, p10[i+1] - 1);
        if(hi >= lo) {
            lens.push_back(hi - lo + 1);
            sums.push_back((Z(lo) + Z(hi)) * (hi - lo + 1) / 2);
        }
    }

    Z res = 0;
    for(int i = 0; i < lens.size(); i++) {
        lens[i]--;
        res += sums[i] * work(lens);
        lens[i]++;
    }

    cout << res << '\n';

    return 0;
}