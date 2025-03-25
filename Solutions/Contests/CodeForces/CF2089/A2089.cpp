#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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
    int p = -1;
    for(int i = (n + 1) / 2, j = (n + 2) / 2; i >= 0 && j < n; i--, j++) {
        if(prime_factor[i] == i) {
            p = i;
            break;
        }
        if(prime_factor[j] == j) {
            p = j;
            break;
        }
    }

    vector<int> res;
    vector<int> used(n + 1);
    if(p != -1) {
        res.push_back(p);
        used[p] = 1;
    }
    for(int i = 1; i < n; i ++) {
        if(p - i <= 0 || p + i > n) break;
        res.push_back(p - i);
        res.push_back(p + i);
        used[p - i] = 1;
        used[p + i] = 1;
    }

    for(int i = 1; i <= n; i++) {
        if(used[i] == 0) res.push_back(i);
    }

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