#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const ll INF = 1'000'000'000'000'000'001LL;

//something not ok with using sqrt ... 

//need to build sieve, typically with N
const int N = 64;;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <ll> prime;

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

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            if(INF / ans < base) return INF;
            ans = ans*base;
        }
        base = base*base;
        power >>= 1;
    }
    return ans;
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

ll nearroot(ll n) {
    ll a = sqrt(n);
    while(a * a > n) a--;
    while((a + 1) * (a + 1) <= n) a++;
    return a;
}

bool issquare(ll n) {
    ll sqn = sqrt(n);
    return sqn * sqn == n;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve();

    ll n; cin >> n;

    ll res = nearroot(n);

    // cout << "start res : " << res << '\n';
    pb_set<ll> vis;

    for(ll p : prime) {
        if(p > 2) {
            ll c = 2;
            while(1) {
                ll next = binexp(c,p);
                if(next <= n) {
                    if(!issquare(next)) {
                        // cout << "add success : " << next << '\n';
                        vis.insert(next);
                    }
                    c++;
                } else {
                    break;
                }
            }
        }
    }

    cout << res + vis.size() << '\n';

    return 0;
}