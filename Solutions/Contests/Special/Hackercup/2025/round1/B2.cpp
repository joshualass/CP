#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
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

constexpr int P = 1e9 + 7;
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

map<array<ll,2>, Z> choose_map;

Z choose_slow(ll n, ll k) {
    if(choose_map.count({n, k}) == 0) {
        Z res = inv_fact[k];
        for(ll i = 1; i <= k; i++) {
            res *= n - i + 1;
        }
        choose_map[{n, k}] = res;
    }
    return choose_map[{n, k}];
}


/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const ll N = 1e7 + 1;

ll prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <ll> prime;

void sieve (ll n = N) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (ll i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
		    prime.push_back(i);
            prime_factor[i] = i;
        }
		for (ll j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

void find_divs(ll idx, ll p, vector<pair<ll,ll>> &facts, Z &res, ll n, ll a, Z ways) {
    if(idx == facts.size()) {
        if(p <= a) {
            res += ways;
        }
        return;
    }
    for(ll j = 0; j < facts[idx].second + 1; j++) {
        Z nx_ways = ways * choose_slow(n - 1 + j, j) * choose_slow(n - 1 + (facts[idx].second - j), facts[idx].second - j);
        find_divs(idx + 1, p, facts, res, n, a, nx_ways);
        p *= facts[idx].first;
    }
}

void prime_factorize(ll num, vector<pair<ll,ll>> &prime_factors) {
    for(ll i = 0; i < prime.size() && 1LL * prime[i] * prime[i] <= num; i++) {
        if(num % prime[i] == 0) {
            prime_factors.push_back({prime[i],0});
            while(num % prime[i] == 0) {
                prime_factors.back().second++;
                num /= prime[i];
            }
        }
        while(num < N && num != 1) {
            ll t = prime_factor[num];
            prime_factors.push_back({t, 0});
            while(num % t == 0) {
                prime_factors.back().second++;
                num /= t;
            }
        }
    }
    if(num != 1) {
        prime_factors.push_back({num,1});
    }
}

//O(sqrt(n)), approx. cuberoot(n) factors. 
void find_divisors(ll num, vector<pair<ll,ll>> &prime_factors, Z &res, ll n, ll a) {
    prime_factorize(num, prime_factors);
    find_divs(0, 1, prime_factors, res, n, a, 1);
}

void solve() {

    ll n, a, b; cin >> n >> a >> b;

    vector<pair<ll,ll>> pf;
    Z res = 0;
    choose_map.clear();
    find_divisors(b, pf, res, n, a);

    cout << res << '\n';
    
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    init_fact();
    sieve();

    freopen("B2in.txt","r",stdin);
    freopen("B2out.txt","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}