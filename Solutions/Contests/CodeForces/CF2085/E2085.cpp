#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const ll N = 1e6 + 1;

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
    find_divs(0, 1, prime_factors, nums);
}

void solve() {
    ll n; cin >> n;

    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    ll d = accumulate(a.begin(), a.end(), 0LL) - accumulate(b.begin(), b.end(), 0LL);
    if(d == 0) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        if(a == b) {
            cout << 1000001 << '\n';
        } else {
            cout << "-1\n";
        }
        return;
    }
    vector<ll> divs;
    find_divisors(d, divs);

    sort(b.begin(), b.end());
    vector<ll> c(n);

    for(ll div : divs) {
        ll diff = 0;
        for(int i = 0; i < n; i++) {
            c[i] = a[i] % div;
            diff += a[i] - c[i];
        }
        if(diff == d) {
            sort(c.begin(), c.end());
            if(c == b) {
                cout << div << '\n';
                return;
            }
        }
    }
    cout << "-1\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}