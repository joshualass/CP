#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//need to build sieve, typically with N
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

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
 
ll gcdExtended(ll a, ll b, ll *x, ll *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

ll dp[2023][4045];
ll dpp[2023][4045];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve();
    memset(dp, 0LL, sizeof(dp));
    memset(dpp, 0LL, sizeof(dpp));

    int n; cin >> n;

    map<ll,ll> m;

    ll res = 1;

    for(int i = 1; i <= n; i++) {
        res = (res * i) % MOD;
    }

    for(int i = 0; i < n * 2; i++) {
        int a; cin >> a;
        m[a]++;
        res = (res * modInverse(m[a],MOD)) % MOD;
    }

    dp[0][0] = 1;
    
    for(int i = 0; i <= 2022; i++) {
        dpp[0][i] = 1;
    }

    for(int i = 1; i <= n; i++) {
        int j = 1;

        for(auto [num, cnt] : m) {
            if(prime_factor[num] == num) {
                dp[i][j] = (dpp[i-1][j-1] * cnt) % MOD;
            }
            j++;
        }

        for(int k = 1; k <= 4044; k++) {
            dpp[i][k] = (dpp[i][k-1] + dp[i][k]) % MOD;
        }

    }

    cout << res * dpp[n][4044] % MOD << '\n';

    return 0;
}