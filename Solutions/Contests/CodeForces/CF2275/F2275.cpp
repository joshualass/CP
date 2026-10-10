#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
array<ll,3> pchash[N];
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

        for(int j = 0; j < 3; j++) {
            pchash[i][j] = rng();
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
vector<pair<ll,int>> find_divisors(int num) {
    vector<pair<ll,int>> prime_factors;
    prime_factorize(num, prime_factors);
    return prime_factors;
}

array<ll,3> operator^(array<ll,3> lhs, array<ll,3> rhs) {
    array<ll,3> res = {};
    for(int i = 0; i < 3; i++) res[i] = lhs[i] ^ rhs[i];
    return res;
}

void solve() {
    
    int n; cin >> n;
    array<ll,3> cur = {};
    map<array<ll,3>,ll> m, q;

    auto hash = [&](int x) -> array<ll,3> {
        auto pf = find_divisors(x);
        array<ll,3> res = {};
        for(auto [p, cnt] : pf) {
            if(cnt & 1) {
                res = res ^ pchash[p];
            }
        }
        return res;
    };

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        array<ll,3> h = hash(x);
        // cout << "x : " << x << " h : " << h << endl;
        cur = cur ^ h;
        m[cur]++;
        q[h]++;
    }

    ll res = 0;

    for(auto [k, v] : q) {
        res += m[k] * v;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    __float128 prob = 1;
    for(int i = 0; i < 1e6; i++) {
        prob *= ((__float128) (ULLONG_MAX - i)) / ((__float128) ULLONG_MAX);
    }

    cout << (ld) prob << endl;

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}