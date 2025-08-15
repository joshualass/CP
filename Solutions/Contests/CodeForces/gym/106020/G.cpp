#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//need to build sieve, typically with N
const int N = 5e6 + 1;

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


void solve() {
    
    int n; cin >> n;
    map<vector<int>, int> dp;
    dp[{}] = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        map<vector<int>, int> nx;
        for(auto [s, score] : dp) {
            vector<int> a = s;
            a.push_back(x);
            sort(a.begin(), a.end());
            for(int j = 0; j < 1 << a.size(); j++) {
                vector<int> test;
                for(int k = 0; k < a.size(); k++) {
                    if((j >> k) & 1) test.push_back(a[k]);
                }
                int ok = 1;
                for(int k = 0; k < test.size(); k++) {
                    for(int l = k + 1; l < test.size(); l++) {
                        if((prime_factor[test[k] ^ test[l]]) != (test[k] ^ test[l])) ok = 0;
                    }
                }
                if(ok) {
                    nx[test] = max(nx[test], score + accumulate(test.begin(), test.end(), 0));
                }
            }
        }
        dp = nx;
    }

    int res = 0;
    for(auto [s, score] : dp) res = max(res, score);
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}