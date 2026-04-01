#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

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
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//need to build sieve, typically with N
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

void solve() {
    
    ll n; cin >> n;
    vector<ll> a(n), b(n), c(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    vector<ll> fixed(n);
    
    ll res = 0;
    for(ll i = 0; i < n; i++) {
        ll t;
        if(i == 0) {
            t = gcd(a[i], a[i+1]);
        } else if(i == n - 1) {
            t = gcd(a[i],a[i-1]);
        } else {
            ll g1 = gcd(a[i],a[i-1]), g2 = gcd(a[i],a[i+1]);
            t = g1 / gcd(g1, g2) * g2;
        }
        c[i] = t;
        if(t <= b[i] && a[i] != t) {
            a[i] = t;
            fixed[i] = 1;
            res++;
        } else if(b[i] < t) {
            fixed[i] = 1;
        }
    }

    // cout << "a : " << a << endl;
    // cout << "b : " << b << endl;
    // cout << "c : " << c << endl;

    vector<array<ll,2>> dp;

    for(ll i = 0; i < n; i++) {
        vector<array<ll,2>> nx;
        ll mx = 0;
        ll g = (i ? gcd(a[i], a[i-1]) : -1);
        for(auto [mul, cnt] : dp) {
            if(gcd(c[i-1] * mul, a[i]) == g) mx = max(mx, cnt);
        }
        // cout << "i : " << i << " mx : " << mx << endl;
        nx.push_back({a[i] / c[i], mx});
        if(fixed[i] == 0) {
            assert(a[i] == c[i]);
            for(ll j = 0; j < 67; j++) {
                ll p = prime[j];
                if(b[i] < a[i] * p) break;
                ll mx = (i ? INT_MIN : 0);
                for(auto [mul, cnt] : dp) {
                    if(gcd(c[i-1] * mul, c[i] * p) == g) {
                        mx = max(mx, cnt);
                    }
                }
                mx++;
                nx.push_back({p, mx});
            }
        }
        swap(dp, nx);
        // cout << "i : " << i << " dp : " << dp << endl;
    }

    ll mx = 0;
    for(auto [mul, cnt] : dp) mx = max(mx, cnt);
    cout << res + mx << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}