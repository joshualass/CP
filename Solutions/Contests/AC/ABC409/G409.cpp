#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
don't be afraid of combo
right stuff down
move things around
work on speed which can then help make observatinos + intuition be stronger. 
*/

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

    // Z nopc = 0;

    // for(int P = 0; P <= 100; P++) {
    //     Z p = Z(P) / 100;
    //     for(int i = 1; i <= 100000 - 1; i++) {
    //         Z res = (1 + (1 - p) / i);
    //         nopc += res;
    //     }
    // }

    // cout << "nopc : " << nopc << '\n';

    ll n, P; cin >> n >> P;
    Z p = Z(P) / 100;

    init_fact(n + 1);

    vector<Z> D(n + 1);
    D[n] = 1;
    for(int i = n - 1; i >= 1; i--) {
        D[i] = D[i+1] * (1 + (1 - p) / i);
    }

    vector<Z> Old_D = D;

    // cout << "Old_D : " << Old_D << '\n';

    for(int i = 2; i <= n; i++) {
        D[i] *= fact[i - 2] * power<Z>(1 - p, i);
    }

    // cout << "D : " << D << '\n';

    // cout << "fact\n";
    // for(int i = 0; i <= n; i++) cout << fact[i] << '\n';
    // cout << "inv fact\n";
    // for(int i = 0; i <= n; i++) cout << inv_fact[i] << '\n';

    vector<Z> y(n);
    for(int i = 0; i < n; i++) {
        y[i] = inv_fact[n - i - 1];
    }

    // cout << "y : " << y << '\n';

    vector<ll> lD(n), ly(n);

    for(int i = 0; i < n; i++) {
        lD[i] = D[i+1].x;
        ly[i] = y[i].x;
    }

    vector<ll> res = convMod<998244353>(lD, ly);

    // cout << "res : " << res << '\n';

    for(int i = n - 1; i < n * 2 - 1; i++) {
        int x = i - (n - 1) + 1;
        if(x == 1) {
            cout << Old_D[1] << '\n';
        } else {
            if(P == 100) {
                cout << "1\n";
            } else {
                cout << res[i] * power<Z>(p, x - 1) / (power<Z>(1 - p, x) * fact[x - 2]) << '\n';
            }
        }
    }


    // cout << "SOLVE SLOWLY (AND HOPEFULLY CORRECTLY) ? \n";
    
    // for(int x = 1; x <= n; x++) {
    //     Z ans = 0;
    //     cout << "x : " << x << '\n';
    //     if(x == 1) {
    //         ans = Old_D[1];
    //     } else {
    //         for(int y = x; y <= n; y++) {
    //             Z lhs = fact[y - 2] / (fact[x - 2] * fact[y - x]) * power<Z>(p, x - 1) * power<Z>(1 - p, y - x);
    //             Z rhs = Old_D[y];
    //             ans += lhs * rhs;
    //             cout << "y : " << y << " lhs : " << lhs << " rhs : " << rhs << '\n';
    //             // ans += fact[max(0, y - 2)] / (fact[max(0, x - 1)] * fact[y - x]) * power<Z>(p, x - 1) * power<Z>(1 - p, y) * D[y];
    //         }
    //     }
    //     cout << "x : " << x << " ans : " << ans << '\n';
    // }

    return 0;
}
