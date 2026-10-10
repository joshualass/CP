#include <bits/stdc++.h>
typedef long long ll;
typedef uint64_t ull;
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
ull pchash[N];
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

        pchash[i] = rng() / 3;
	}
}

void find_divs(int idx, int p, vector<pair<ull,int>> &facts, vector<int> &nums) {
    if(idx == facts.size()) {
        nums.push_back(p);
        return;
    }
    for(int j = 0; j < facts[idx].second + 1; j++) {
        find_divs(idx + 1, p, facts, nums);
        p *= facts[idx].first;
    }
}

void prime_factorize(ull num, vector<pair<ull,int>> &prime_factors) {
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
vector<pair<ull,int>> find_divisors(int num) {
    vector<pair<ull,int>> prime_factors;
    prime_factorize(num, prime_factors);
    return prime_factors;
}

void solve() {
    
    int n; cin >> n;
    ull cur = 0;
    map<ull,ull> m, q;

    auto hash = [&](int x) -> ull {
        auto pf = find_divisors(x);
        ull res = 0;
        for(auto [p, cnt] : pf) {
            if(cnt & 1) {
                res ^= pchash[p];
            }
        }
        return res;
    };

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ull h = hash(x);
        // cout << "x : " << x << " h : " << h << endl;
        cur ^= h;
        m[cur]++;
        q[h]++;
    }

    ull res = 0;

    for(auto [k, v] : q) {
        res += m[k] * v;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}