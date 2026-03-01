#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//need to build sieve, typically with N
const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <int> prime;

void sieve (int n = N) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (int i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
		    prime.push_back(i);
            prime_factor[i] = i;
        }
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();
    
    ll n, m; cin >> n >> m;
    vector<int> cnts(m + 1), bad(m + 1);
    for(int i = 2; i <= m; i++) {
        if(prime_factor[i] == i) {
            for(int j = i; j <= m; j += i) {
                cnts[j] ^= 1;
            }
            for(ll j = 1LL * i * i; j <= m; j += i * i) {
                bad[j] = 1;
            }
        }
    }

    // vector<int> testres(m + 1);
    // for(int i = 1; i <= m; i++) {
    //     for(int j = i; j <= m; j += i) {
    //         if(bad[i] == 0) {
    //             testres[j] += cnts[i] ? -1 : 1;
    //         }
    //     }
    // }

    // cout << testres << '\n';

    vector<array<int,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    Z res = 0;
    
    auto get_ways_gcd = [&](int g) -> Z {
        int cap = m / g;
        vector<Z> dpp(cap + 1), ndpp(cap + 1);
        dpp[cap] = 1;
        // cout << "g : " << g << " cap : " << cap << endl;
        // cout << "starting dp : " << dpp << endl;
        for(int i = 0; i < n; i++) {
            int lo = (a[i][0] + g - 1) / g;
            int hi = a[i][1] / g;
            // cout << "lo : " << lo << " hi : " << hi << endl;
            for(int j = 0; j <= cap; j++) {
                ndpp[j] = dpp[min(cap, hi + j)] - dpp[min(cap, lo - 1 + j)];
                if(j) ndpp[j] += ndpp[j-1];
            }
            swap(dpp, ndpp);
            // cout << "i : " << i << " dp : " << dpp << endl;
        }
        return dpp.back();
    };

    for(int i = 1; i <= m; i++) {
        if(bad[i] == 0) {
            Z ways = get_ways_gcd(i);
            // cout << "i : " << i << " ways : " << ways << endl;
            if(cnts[i] == 0) {
                res += ways;
            } else {
                res -= ways;
            }
        }
    }

    cout << res << '\n';

    return 0;
}
