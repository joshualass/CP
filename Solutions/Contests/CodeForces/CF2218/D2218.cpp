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
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            cout << prime[i] << " ";
        } else {
            cout << 1LL * prime[i-1] * prime[i] << " ";
        }
    }

    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}