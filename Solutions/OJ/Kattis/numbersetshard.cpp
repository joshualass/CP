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

int dsu[N * 2];
int sizes[N * 2];

void dsubuild(int n) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    // cout << "find x : " << x << endl;
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    // cout << "merge x : " << x << " y : " << y << endl;
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[y] = x;
        sizes[x] += sizes[y];
    }
}

void solve() {

    ll a, b, p; cin >> a >> b >> p;
    int n = b - a + 1;
    // cout << "build sz : " << n + prime.size() << '\n';
    dsubuild(n + prime.size());
    int sz = n;
    int pt = n;
    for(ll pr : prime) {
        int f = 0;
        if(pr >= p) {
            for(ll i = (a + pr - 1) / pr * pr; i <= b; i += pr) {
                f = 1;
                // cout << "i : " << i << " i - a : " << i - a << " pt : " << pt << endl;
                if(find(i - a) != find(pt)) {
                    sz--;
                    merge(i - a, pt);
                }
            }
        }
        pt++;
        sz += f;
    }

    cout << sz << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();
    // cout << "pc size : " << prime.size() << '\n';
    // ld res = 0;
    // for(ll x : prime) res += 1.0 / x;
    // cout << "res : " << res << '\n';

    int casi; cin >> casi;

    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}