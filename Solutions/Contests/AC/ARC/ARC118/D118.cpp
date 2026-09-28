#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 42069;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();
    ll p, a, b; cin >> p >> a >> b;

    if(p == 2) {
        cout << "Yes\n1 1\n";
        return 0;
    }

    // vector<ll> divs;
    // find_divisors(p - 1, divs);

    // // cout << "divs : " << divs << '\n';

    // for(ll t = 0; t < 8; t++) {
    //     ll ia = binexp(a, p - 2, p), ib = binexp(b, p - 2, p);
    //     for(ll div : divs) {
    //         if(div % 2 == 0) {
    //             ll s2 = (p - 1) / div - 1;
    //             vector<ll> vis(p), order;
    //             ll res = 1;
    //             for(ll i = 0; i < div; i++) {
    //                 if(vis[res] == 0) {
    //                     order.push_back(res);
    //                     vis[res] = 1;
    //                 }
    //                 for(ll j = 0; j < s2; j++) {
    //                     if(i & 1) {
    //                         res = res * ib % p;
    //                     } else {
    //                         res = res * b % p;
    //                     }
    //                     if(vis[res] == 0) {
    //                         order.push_back(res);
    //                         vis[res] = 1;
    //                     }
    //                 }
    //                 res = res * a % p;
    //             }

    //             // cout << "t : " << t << " a : " << a << " b : " << b << '\n' << " vis : " << vis << "\norder " << order << '\n';

    //             if(order.size() == p - 1) {
    //                 cout << "Yes\n";
    //                 for(ll x : order) cout << x << " ";
    //                 cout << "1\n";
    //                 return 0;
    //             }
    //         } 
    //     }
    //     if(t & 1) {
    //         swap(a,b);
    //     } else {
    //         a = ia;
    //     }
    // }

    auto get_pd = [&](ll i, set<ll> &s) -> ll {
        ll c = i, pd = 1;
        while(s.count(c) == 0) {
            pd++;
            s.insert(c);
            c = c * i % p;
        }
        return pd;
    };

    set<ll> s;
    s.insert(1);
    ll n = get_pd(a, s);
    ll m = get_pd(b, s);

    // cout << "n : " << n << " m : " << m << '\n';

    if(n * m == p - 1) {
        cout << "Yes\n";
        if(n & 1) {
            s.clear();
            swap(a,b);
            s.insert(1);
            n = get_pd(a, s);
            m = get_pd(b, s);
        }
        ll ib = binexp(b, p - 2, p);
        ll c = 1;
        for(int i = 0; i < n; i++) {
            cout << c << " ";
            for(int j = 0; j < m - 1; j++) {
                if(i & 1) {
                    c = c * ib % p;
                } else {
                    c = c * b % p;
                }
                cout << c << " ";
            }
            c = c * a % p;
        }
        cout << "1\n";
    } else {

        cout << "No\n";
    }


    return 0;
}