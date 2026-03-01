#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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


void solve() {
    
    int n; cin >> n;
    int p = 1, f = 0;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    for(int i = 0; i < n; i++) {
        int x = a[i];
        int pmin = INT_MAX, pmax = INT_MIN;
        if(x == 1) {
            pmin = 1, pmax = 1;
        } else {
            while(x != 1) {
                pmin = min(pmin, prime_factor[x]);
                pmax = max(pmax, prime_factor[x]);
                x /= prime_factor[x];
            }
        }

        if(pmin != pmax) f = 1;
        if(pmin < p) f = 1;
        p = pmin;
    }

    if(is_sorted(a.begin(), a.end())) f = 0;

    cout << (f ? "Alice" : "Bob") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}