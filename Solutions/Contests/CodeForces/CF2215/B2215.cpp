#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const ll N = 2e6 + 1;

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

void find_divs(ll idx, ll p, vector<pair<ll,ll>> &facts, vector<ll> &nums) {
    if(idx == facts.size()) {
        nums.push_back(p);
        return;
    }
    for(ll j = 0; j < facts[idx].second + 1; j++) {
        find_divs(idx + 1, p, facts, nums);
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
void find_divisors(ll num, vector<ll> &nums) {
    vector<pair<ll,ll>> prime_factors;
    prime_factorize(num, prime_factors);
    // cout << "num : " << num << " pf : " << prime_factors << endl;
    find_divs(0, 1, prime_factors, nums);
}

void solve() {
    
    ll n; cin >> n;
    ll res = 0;

    vector<ll> a(100);

    for(ll b = 2; b * b <= n; b++) {
        ll t = n;
        int s = 0;
        while(t) {
            a[s++] = t % b;
            t /= b;
        }
        
        for(ll p = 2; p <= s; p++) {
            if(s % p) continue;
            ll ok = 1;
            for(ll j = 0 && ok; j * p < s; j++) {
                for(ll i = 1; i < p && ok; i++) {
                    if(a[j * p + i] != a[j * p]) ok = 0;
                }
            }
            if(ok) res++;
        }
    }

    // cout << "im res : " << res << endl;

    vector<ll> divs;
    find_divisors(n, divs);

    // cout << "divs : " << divs << endl;

    for(ll b : divs) {
        b--;
        if(n % (b + 1) == 0) {
            ll d = n / (b + 1);
            if(d < b) {
                res++;
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}