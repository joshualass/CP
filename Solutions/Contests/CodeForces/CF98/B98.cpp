#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << "/";
        }
    }
    return os;
}

array<ll,2> add(array<ll,2> a, array<ll,2> b) {
    array<ll,2> res = {a[0] * b[1] + a[1] * b[0], a[1] * b[1]};
    ll g = gcd(res[0], res[1]);
    res[0] /= g;
    res[1] /= g;
    return res;
}

array<ll,2> sub(array<ll,2> a, array<ll,2> b) {
    array<ll,2> res = {a[0] * b[1] - a[1] * b[0], a[1] * b[1]};
    ll g = gcd(res[0], res[1]);
    res[0] /= g;
    res[1] /= g;
    return res;
}

array<ll,2> mul(array<ll,2> a, array<ll,2> b) {
    array<ll,2> res = {a[0] * b[0], a[1] * b[1]};
    ll g = gcd(res[0], res[1]);
    res[0] /= g;
    res[1] /= g;
    return res; 
}

array<ll,2> lo(array<ll,2> a, array<ll,2> b) {
    if(a[0] * b[1] < b[0] * a[1]) {
        return a;
    } else {
        return b;
    }
}

array<ll,2> pc[10001];

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
void find_divisors(int num, vector<int> &nums) {
    vector<pair<ll,int>> prime_factors;
    prime_factorize(num, prime_factors);
    find_divs(0, 1, prime_factors, nums);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    auto get_flips = [](int n) -> array<ll,2> {
        int flips = ceil(log2(n));
        int a = 1 << flips;

        array<ll,2> lhs = {1,1};
        array<ll,2> rhs = mul(array<ll,2>{flips,1}, array<ll,2>{n, a});

        int left = a - n;

        for(int i = 0; i < flips; i++) {
            if((left >> (flips - 1 - i)) & 1) {
                array<ll,2> f = {1, 1 << (i + 1)};
                int fc = i + 1;
                lhs = sub(lhs, f);
                rhs = add(rhs, mul(f, array<ll,2>{fc, 1}));
            }
        }

        array<ll,2> res = mul(rhs, array<ll,2>{lhs[1], lhs[0]});
        return res;
    };

    for(int i = 1; i <= 10000; i++) {
        pc[i] = get_flips(i);
    }

    int n; cin >> n;

    vector<array<ll,2>> dp(n + 1, array<ll,2>{10000, 1});

    for(int i = 1; i <= n; i++) {
        vector<int> divs;
        find_divisors(i, divs);
        dp[i] = pc[i];
        for(int div : divs) {
            dp[i] = lo(dp[i], add(dp[i/div], dp[div]));
        }
        cout << "i : " << i << " dp[i] : " << dp[i] << " vs " << pc[i] << '\n';
    }

    cout << dp[n] << '\n';

    return 0;
}