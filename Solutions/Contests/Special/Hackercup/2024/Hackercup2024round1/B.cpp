#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//need to build sieve, typically with N
const int N = 1e7 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
int p[N];
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
    cout << p[n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);

    sieve();

    memset(p, 0, sizeof(p));
    p[5]++; 
    for(int i = 5; i < N; i++) {
        if(prime_factor[i-2] == i - 2 && prime_factor[i] == i) {
            p[i]++;
        }
        p[i] += p[i-1];
    }

    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}