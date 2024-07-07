#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const int N = 1e6 + 1;
ll pref[N];
ll a[N];
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
    cout << a[n] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(pref,0,sizeof(pref));
    memset(a,0,sizeof(a));
    sieve();

    for(ll i = 2; i < N; i++) {
        if(prime_factor[i] == i) {
            for(ll j = 1; j * i < N; j++) {
                // cout << "i : " << i << " j : " << j << " sub idx : " << j * i << '\n';
                pref[j * i]--;
                if(j % i == 1) {
                    pref[j * i] += i;
                    // cout << "i : " << i << " j : " << j << " add idx : " << j * i << " val : " << i << '\n';
                }
            }
        }
        if(i == 4) {
            for(ll j = 1; j * i < N; j++) {
                pref[j * i] -= 2;
                // cout << "i : " << i << " j : " << j << " sub idx : " << j * i << " sub 2 : " << '\n';
                if(j % 2 == 1) {
                    pref[j * i] += i;
                    // cout << "i : " << i << " j : " << j << " add idx : " << j * i << " val : " << i << '\n';
                }
            }
        }
    }

    ll c = 0, d = 0;
    for(ll i = 1; i < N; i++) {
        c += pref[i];
        d = ((d + c) % MOD + MOD) % MOD;
        a[i] = d;
        // cout << "i : " << i << " pref[i] : " << pref[i] << " a[i] : " << a[i] << '\n';
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}