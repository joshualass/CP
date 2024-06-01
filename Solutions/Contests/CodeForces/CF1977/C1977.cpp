#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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

//O(sqrt(n)), approx. cuberoot(n) factors. 
void find_divisors(ll num, vector<ll> &nums) {
    // map<ll,ll> factors;
    vector<pair<ll,ll>> factors;
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
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    set<ll> s(a.begin(), a.end());
    ll hi = *max_element(a.begin(), a.end());
    bool found = 0;
    for(ll i = 0; i < n; i++) {
        if(hi % a[i] != 0) found = 1;
    }
    if(found) {
        cout << n << '\n';
        return;
    }
    vector<ll> divs;
    find_divisors(hi,divs);

    ll res = 0;
    for(ll x : divs) {
        ll curr_lcm = 1;
        ll cnt = 0;
        for(ll i = 0; i < n; i++) {
            if(x % a[i] == 0) {
                curr_lcm = curr_lcm * a[i] / gcd(curr_lcm, a[i]);
                cnt++;
            }
        }
        // cout << "x : " << x << " clcm : " << curr_lcm << '\n';
        if(curr_lcm == x && s.count(x) == 0) {
            res = max(res,cnt);
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