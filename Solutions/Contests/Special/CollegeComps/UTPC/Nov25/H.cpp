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
lots of impl errors. 

the correct way to do pie is to first ensure that all of the numbers are square free. 
now, after the numbers are square free, consider some small examples such as (2), (2, 3), and (2,3,5). 
From these small examples, we should see that we should look at the parity of the number of prime factors. 

For the square free numbers to do PIE :)
*/

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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int debug = 0;

void test(int n, int m) {

    vector<vector<int>> divs(m + 1);
    vector<int> sign(m + 1);
    for(int i = 1; i <= m; i++) {
        vector<pair<ll,int>> pf;
        prime_factorize(i, pf);
        int ok = 1;
        for(auto [p, cnt] : pf) {
            if(cnt != 1) ok = 0;
        }
        if(ok) {
            if(pf.size() & 1) {
                sign[i] = -1;
            } else {
                sign[i] = 1;
            }
        }
        find_divs(0, 1, pf, divs[i]);
        // find_divisors(i, divs[i]);
    }

    //returns {count, {num, den}}
    auto get = [&](ll num) -> pair<int,array<int,2>> {
        int res = 0;
        array<int,2> mx = {0,1};
        for(int d = 1; d <= m; d++) {
            int z = min((ll) (num * d / 1e9), (ll) n);
            if(1LL * z * mx[1] > 1LL * d * mx[0]) mx = array<int,2>{z, d};
            int cnt = 0;
            map<int,int> mapa;
            for(int div : divs[d]) {
                cnt += (z / div) * sign[div];
                // if(divs[div].size() == 1) {
                //     cnt += z / div;
                //     for(int j = 1; j * div <= z; j++) mapa[j * div]++;
                // } else if(divs[div].size() == 2) {
                //     cnt -= z / div;
                //     for(int j = 1; j * div <= z; j++) mapa[j * div]--;
                // } else if(divs[div].size() == 4) {
                //     sort(divs[div].begin(), divs[div].end());
                //     if(1LL * divs[div][1] * divs[div][1] * divs[div][1] != divs[div][3]) {
                //         cnt += z / div;
                //         for(int j = 1; j * div <= z; j++) mapa[j * div]++;
                //     }
                // }
            }
            if(debug) {
                int check = 0;
                for(int j = 1; j <= z; j++) {
                    if(gcd(j, d) == 1) check++;
                }
                if(check != cnt) {
                    cout << "d : " << d << " z : " << z << " cnt : " << cnt << " check : " << check << '\n';
                    cout << "minato namikaze\n";
                    cout << "mapa \n" << mapa << '\n';
                    assert(0);
                }
            }
            res += cnt;
        }
        return {res, mx};
    };

    vector<array<int,2>> a;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(gcd(i,j) == 1) a.push_back({i,j});
        }
    }

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[0] * rhs[1] < lhs[1] * rhs[0];
    });

    // for(int qq = 0; qq < q; qq++) {
    //     int targ; cin >> targ;
    for(int targ = 1; targ <= n * m; targ++) {
        ll l = 1, r = 1e14;
        while(l != r) {
            ll m = (l + r) / 2;
            auto [cnt, f] = get(m);
            if(cnt < targ) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        if(l == 1e14) {
            if(targ <= a.size()) {
                cout << "Trick\n";
                cout << "targ should not be a trick!\n";
                cout << "n : " << n << " m : " << m << '\n';
                cout << "targ : " << targ << endl;
                cout << "a : " << a << endl;
                assert(0);
            }
        } else {
            auto f = get(l);
            if(targ > a.size()) {
                cout << "should be a trick but getting : " << f.second[0] << "/" << f.second[1] << '\n';
                cout << "targ : " << targ << '\n';
                assert(0);
            }
            if(f.second != a[targ - 1]) {
                cout << f.second[0] << "/" << f.second[1] << '\n';
                cout << "got diff sol'n : " << a[targ - 1][0] << "/" << a[targ - 1][1] << '\n';
                assert(0);
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    // test(1000, 1000);

    // for(int i = 1; i <= 50; i++) {
    //     for(int j = 1; j <= 50; j++) {
    //         test(i, j);
    //     }
    // }

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> divs(m + 1);
    vector<int> sign(m + 1);
    for(int i = 1; i <= m; i++) {
        vector<pair<ll,int>> pf;
        prime_factorize(i, pf);
        int ok = 1;
        for(auto [p, cnt] : pf) {
            if(cnt != 1) ok = 0;
        }
        if(ok) {
            if(pf.size() & 1) {
                sign[i] = -1;
            } else {
                sign[i] = 1;
            }
        }
        find_divs(0, 1, pf, divs[i]);
        // find_divisors(i, divs[i]);
    }

    //returns {count, {num, den}}
    auto get = [&](ll num) -> pair<int,array<int,2>> {
        int res = 0;
        array<int,2> mx = {0,1};
        for(int d = 1; d <= m; d++) {
            int z = min((ll) (num * d / 1e9), (ll) n);
            if(1LL * z * mx[1] > 1LL * d * mx[0]) mx = array<int,2>{z, d};
            int cnt = 0;
            map<int,int> mapa;
            for(int div : divs[d]) {
                cnt += (z / div) * sign[div];
                // if(divs[div].size() == 1) {
                //     cnt += z / div;
                //     for(int j = 1; j * div <= z; j++) mapa[j * div]++;
                // } else if(divs[div].size() == 2) {
                //     cnt -= z / div;
                //     for(int j = 1; j * div <= z; j++) mapa[j * div]--;
                // } else if(divs[div].size() == 4) {
                //     sort(divs[div].begin(), divs[div].end());
                //     if(1LL * divs[div][1] * divs[div][1] * divs[div][1] != divs[div][3]) {
                //         cnt += z / div;
                //         for(int j = 1; j * div <= z; j++) mapa[j * div]++;
                //     }
                // }
            }
            if(debug) {
                int check = 0;
                for(int j = 1; j <= z; j++) {
                    if(gcd(j, d) == 1) check++;
                }
                // if(check != cnt) {
                //     cout << "d : " << d << " z : " << z << " cnt : " << cnt << " check : " << check << '\n';
                //     cout << "minato namikaze\n";
                //     cout << "mapa \n" << mapa << '\n';
                //     assert(0);
                // }
            }
            res += cnt;
        }
        return {res, mx};
    };

    for(int qq = 0; qq < q; qq++) {
        int targ; cin >> targ;
        ll l = 1, r = 1e14;
        while(l != r) {
            ll m = (l + r) / 2;
            auto [cnt, f] = get(m);
            if(cnt < targ) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        if(l == 1e14) {
            cout << "Trick\n";
        } else {
            auto f = get(l);
            cout << f.second[0] << "/" << f.second[1] << '\n';
        }
    }

    return 0;
}
