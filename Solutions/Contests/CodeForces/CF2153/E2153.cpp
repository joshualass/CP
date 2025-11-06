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
#include <cstring>
typedef long long ll;
typedef long double ld;
using namespace std;

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

void find_divs(int idx, int p, vector<pair<ll,int>> &facts, vector<int> &nums) {
    if(idx == facts.size()) {
        nums.push_back(p);
        return;
    }
    for(int j = 0; j < facts[idx].second + 1; j++) {
        find_divs(idx + 1, p, facts, nums);
        p *= facts[idx].first;
    }
}

void prime_factorize(ll num, vector<pair<ll,int>> &prime_factors) {
    for(int i = 0; i < prime.size() && 1LL * prime[i] * prime[i] <= num; i++) {
        if(num % prime[i] == 0) {
            prime_factors.push_back({prime[i],0});
            while(num % prime[i] == 0) {
                prime_factors.back().second++;
                num /= prime[i];
            }
        }
        while(num < N && num != 1) {
            int t = prime_factor[num];
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
void find_divisors(int num, vector<int> &nums) {
    vector<pair<ll,int>> prime_factors;
    prime_factorize(num, prime_factors);
    find_divs(0, 1, prime_factors, nums);
}

ll vp(ll p, ll x) {
    ll res = 0;
    ll div = 1;
    for(int j = 1; ; j++) {
        div *= p;
        if(div > x) break;
        res += x / div;
    }
    return res;
}

ll vk(ll k, ll x) {
    if(x == 1) return 0;
    if(prime_factor[k] == k) {
        return vp(k, x);
    } else {
        ll res = LLONG_MAX;
        vector<pair<ll,int>> pf;
        prime_factorize(k, pf);
        for(auto [p, e] : pf) {
            ll vpx = vp(p, x);
            res = min(res, vpx / e);
        }
        return res;
    }
}

ll wk(ll k, ll a, ll b) {
    ll vka = vk(k, a), vkb = vk(k, b);
    if(vka != vkb) {
        return vka;
    } else {
        return 1e18;
    }
}

ll fm(ll m, ll a, ll b) {
    ll res = LLONG_MAX;
    for(int k = 2; k <= m; k++) {
        res = min(res, wk(k, a, b));
    }
    if(res > 1) {
        cout << "m : " << m << " a : " << a << " b : " << b << '\n';
        cout << "res : " << res << '\n';
        assert(0);
    }
    return res;
}

ll solve_slow(ll n, ll m) {
    ll res = 0;
    for(int x = 1; x <= n - 1; x++) {
        res += fm(m, x, n);
    }
    return res;
}

void solve() {
    
    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int tc; cin >> tc;
    for(int i = 0; i < tc; i++) {
        int n, m; cin >> n >> m;
        cout << solve_slow(n, m) << '\n';
    }

    // for(int k = 2; k <= 10; k++) {
    //     for(int x = 1; x <= 10; x++) {
    //         cout << "k : " << k << " x : " << x << " vk : " << vk(k, x) << '\n';
    //     }
    // }

    for(int n = 10; n <= 100; n++) {
        for(int m = n; m <= 100; m++) {
            ll res = solve_slow(n, m);
            cout << "n : " << n << " m : " << m << " solve_slow : " << res << '\n';
        }
    }

    // for(int a = 1; a < 100; a++) {
    //     cout << "a : " << a << " fm()"
    // }

    // int casi; cin >> casi;
    // while(casi-->0) solve();

    return 0;
}