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

void solve() {
    
    int n; cin >> n;
    vector<array<int,2>> a(n);
    for(auto &x : a) cin >> x[0];
    for(auto &x : a) cin >> x[1];

    sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) -> bool {
        return lhs[1] < rhs[1];
    });

    //this should always hold, we can do this, always. 
    ll res = a[0][1] + a[1][1];

    auto get_pf = [&](int x) -> vector<int> {
        vector<int> pf;
        for(int i = 2; i <= sqrt(x + 0.1); i++) {
            if(x % i == 0) {
                pf.push_back(i);
                while(x % i == 0) x /= i;
            }
        }
        if(x != 1) pf.push_back(x);
        return pf;
    };
    
    map<int,int> pf_freq;
    for(int i = 0; i < n; i++) {
        auto pf = get_pf(a[i][0]);
        for(int p : pf) pf_freq[p]++;
    }

    //case do 0 ops
    for(auto [k, v] : pf_freq) {
        if(v >= 2) res = 0;
    }

    //case do a single op on any element
    auto test = [&](int idx, int ops) -> void {
        auto pf = get_pf(a[idx][0]);
        for(auto p : pf) pf_freq[p]--;
        int val = a[idx][0] + ops;
        pf = get_pf(val);
        for(auto p : pf) {
            if(pf_freq[p]) res = min(res, 1LL * a[idx][1] * ops);
        }
        pf = get_pf(a[idx][0]);
        for(auto p : pf) pf_freq[p]++;
    };

    for(int i = 0; i < n; i++) test(i, 1);

    //find the earliest time that it works for the minimum b_i element. 
    //we cannot escape the sieve!

    // i dont think this is correct, what if it's large, i.e. 8 vs 7

/*
tc

2
8 7
1 100


*/



    for(int i = 1; i < n; i++) {
        vector<int> nums;
        find_divisors(a[i][0], nums);
        for(int x : nums) {
            if(x != 1) {
                ll dist = (x - a[0][0]) % x;
                if(dist < 0) dist += x;
                res = min(res, 1LL * a[0][1] * dist);
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}