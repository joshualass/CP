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

void solve() {
    int n; cin >> n;
    int d = 0;
    while(1) {
        d++;
        int tri = d * (d - 1) / 2;
        int self = d;
        if(d & 1) {
            if(tri + self + 1 >= n) break;
        } else {
            if(tri + self + 1 - (d / 2 - 1) >= n) break;
        }
    } 

    vector<int> res;
    for(int i = 0; i < d; i++) {
        res.push_back(i);
        res.push_back(i);
        for(int length = 2; length < (d + 1) / 2; length++) {
            int g = gcd(d,length);
            if(i < g) {
                for(int j = 0; j < d / g; j++) {
                    res.push_back((res.back() + length) % d);
                }
            }
        }
    }
    
    res.push_back(0);
    if(d % 2 == 0) res.push_back(d/2);

    for(int i = 0; i < n; i++) {
        cout << prime[res[i]] << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}