#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll binexp(ll base, ll power, ll mod = MOD) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%mod;
        }
        base = base*base%mod;
        power >>= 1;
    }
    return ans;
}

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
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

void find_divs(int idx, int p, vector<pair<int,int>> &facts, vector<int> &nums) {
    if(idx == facts.size()) {
        nums.push_back(p);
        return;
    }
    for(int j = 0; j < facts[idx].second + 1; j++) {
        find_divs(idx + 1, p, facts, nums);
        p *= facts[idx].first;
    }
}

//O(sqrt(n)), approx. cuberoot(n) factors. 
vector<pair<int,int>> find_divisors(int num) {
    // map<int,int> factors;
    vector<pair<int,int>> factors;
    // cout << "num: " << num << " ";
    for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
        bool first = 1;
        while(num % prime[i] == 0) {
            if(first) {
                factors.push_back({prime[i],1});
                first = 0;
            } else {
                factors.back().second++;
            }
            num /= prime[i];
        }
    }
    if(num != 1) {
        factors.push_back({num,1});
    }
    return factors;
}

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m = MOD) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
 
ll gcdExtended(ll a, ll b, ll *x, ll *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
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

constexpr int P = 781044643;
using Z = Mint<P>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // sieve();

    // cout << binexp(17, 3030, 19079) << '\n';
    // cout << binexp(17, 6892, 19079) << '\n';
    // cout << binexp(17, 18312, 19079) << '\n';

    // cout << "14580 : " << find_divisors(14580) << '\n';
    // cout << "18432 : " << find_divisors(18432) << '\n';
    // cout << "6000 : " << find_divisors(6000) << '\n';

    // cout << modInverse(2, 9539) << '\n';
    // cout << 2 * 4770 % MOD << ", " << 6 * 4770 % MOD << ", " << 4770 << ", " << 3030 * 4770 % MOD << '\n';
    // cout << (2 + 3 * -11 + MOD) % MOD << ", " << (0 + 4770 * -11 + MOD * MOD) % MOD << ", " << (6892 + 1515 * -11 + MOD * MOD) % MOD << '\n';
    // cout << (4 + 1 * -4 + MOD) % MOD << ", " << (1 + 3 * -4 + MOD) % MOD << ", " << (3 - 4770 * -4 + MOD * MOD) % MOD << ", " << (8773 + 1515 * -4 + MOD * MOD) % MOD << '\n';
    // cout << modInverse(9508) << '\n';
    // cout << (0 * 7385) % MOD << ", " << (9508 * 7385) % MOD << ", " << (4764 * 7385) % MOD << ", " << 9305 * 7385 % MOD << '\n';
    // cout << "0, 0, " << (5 + 2308 * -9528 + MOD * MOD) % MOD << ", " << (2713 + 8008 * -9528 + MOD * MOD) % MOD << "\n";
    // cout << modInverse(6315) << '\n';
    // cout << 4950 * 5666 % MOD << '\n';
    // cout << (8008 + 2040 * -2308 + MOD * MOD) % MOD << '\n';
    // cout << (1515 + 2040 * -4770 + MOD * MOD) % MOD << "\n";
    // cout << (495 + 2415 * -3 + MOD) % MOD << '\n';
    // cout << modInverse(2) << '\n';
    // cout << (2789 * 4770) % MOD << '\n';
    // cout << 12328 % MOD << '\n';
    // cout << (19 * binexp(modInverse(17),12400)) % MOD << '\n';
    // cout << "divisors are : " << find_divisors((19 * binexp(modInverse(17),12400)) % MOD) << '\n';
    // cout << (7*17734 + 10838 + 12400) % MOD << '\n';

    // cout << binexp(17,13830) << '\n';

    // MOD = 11;
    // while(1) {
    //     set<int> s;
    //     for(int i = 0; i < MOD; i++) {
    //         s.insert(binexp(i,3));
    //     }
    //     for(int x : s) {
    //         for(int y : s) {
    //             if(s.count(x*y%MOD) == 0) {
    //                 cout << "x : " << x << " y : " << y << '\n';
    //                 for(int i = 0; i < MOD; i++) {
    //                     cout << "i : " << i << " binexp : " << binexp(i,3) << '\n';
    //                 }
    //                 return 0;
    //             }
    //         }
    //     }
    //     MOD++;
    // }

    // for(int i = 0; i < MOD; i++) {
    //     cout << "i : " << i << " binexp : " << binexp(i,3) << '\n';
    // }
    // Z a = 1, r = 631364468;
    // cout << a * r * r << '\n';

    MOD = (781044643);
    // cout << modInverse(159853) << '\n';

    // cout << ((5584-6104*3534)%MOD * modInverse(4451) % MOD + MOD) % MOD << '\n';

    // cout << ((5584-6104*3534)*modInverse(4451) % MOD + MOD) % MOD << '\n';
    ll a = 67651321;
    cout << a*a % MOD << '\n';

    return 0;
}