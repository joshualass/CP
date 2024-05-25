#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

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

void find_divisors(int num, vector<int> &nums) {
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
    // cout << factors << "\n";
    find_divs(0, 1, factors, nums);
}

void solve() {
    int n; cin >> n;
    unordered_map<int,ll> m;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        m[num]++;
    }
    ll res = 0;
    for(auto [u, v] : m) {
        //let element u be a_j
        if(u <= 1000000) {
            vector<int> factors;
            find_divisors(u,factors);
            // cout << "num : " << u << " f : " << factors << '\n';
            for(int factor : factors) {
                if(factor != u) {
                    int b = u / factor;
                    if(1000000000 / u >= b && m.find(factor) != m.end() && m.find(u * b) != m.end()) {
                        res += m[factor] * m[u] * m[u * b];
                    }
                }
            }
        } else {
            for(int b = 2; b * u <= 1000000000; b++) {
                if(u % b == 0) {
                    if(m.find(u/b) != m.end() && m.find(u * b) != m.end()) {
                        res += m[u/b] * m[u] * m[u*b];
                    }
                }
            }
        }
        // cout << "add sames u : " << u << " v : " << v << " val : " << v * (v - 1) * (v - 2) << '\n';
        res += v * (v - 1) * (v - 2);
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    // freopen("g.in","r",stdin);
    // freopen(".out","w",stdout);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}