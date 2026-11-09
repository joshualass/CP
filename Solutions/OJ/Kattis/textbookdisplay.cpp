// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n = 3000;
//     cout << n << endl;
//     for(int i = 1; i <= n; i++) {
//         cout << (rng() % 1000001) / i << " \n"[i == n];
//     }    

//     return 0;
// }



#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

//need to build sieve, typically with N
const int N = 1e6 + 1;
const int P = 17;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> dp(1 << P);
    dp[0] += a[0];
    a.insert(a.begin(), 0);

    for(int i = 2; i <= n; i++) {
        int use = 0;
        int t = i;
        for(int j = 0; j < P; j++) {
            if(t % prime[j] == 0) use += 1 << j;
            while(t % prime[j] == 0) t /= prime[j];
        }
        if(t == 1) {
            int not_use = ((1 << P) - 1) ^ use;
            for(int k = not_use; k >= 0; --k &= not_use) {
                dp[k | use] = max(dp[k | use], dp[k] + a[i]);
                if(k == 0) break;
            }
        }
    }

    vector<int> ndp(1 << P);
    for(int i = P; prime[i] <= 3000; i++) {
        ndp = dp;
        for(int j = 1; prime[i] * j <= n; j++) {
            int t = prime[i] * j;
            // cout << "t : " << t << endl;
            int use = 0;
            for(int j = 0; j < P; j++) {
                if(t % prime[j] == 0) use += 1 << j;
                while(t % prime[j] == 0) t /= prime[j];
            }
            assert(t == prime[i]);
            int not_use = ((1 << P) - 1) ^ use;
            for(int k = not_use; k >= 0; --k &= not_use) {
                ndp[k | use] = max(ndp[k | use], dp[k] + a[prime[i] * j]);
                if(k == 0) break;
            }
        }
        dp = ndp;
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}
