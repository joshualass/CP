#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    os << "{ ";
    for(auto x : v) os << x << " ";
    os << '}';
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

//need to build sieve, typically with N
const int N = 2e7 + 1;

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

vector<int> getprimes(int x) {
    vector<int> elprimo;
    while(x != 1 && x) {
        elprimo.push_back(prime_factor[x]);
        x /= prime_factor[x];
    }
    sort(elprimo.begin(), elprimo.end());
    return elprimo;
}


void solve() {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    cerr << "sieve is done\n";

    vector<vector<int>> poss(10000,vector<int>(10000));

    for(int i = 0; i < 10000; i++) {
        for(int j = 0; j < 10000; j++) {
            if(i == 0 || j == 0) {
                poss[i][j] = 1;
            } else {
                if(gcd(i,j) == 1 && (poss[i-1][j] || poss[i][j-1])) {
                    poss[i][j] = 1;
                }
            }
        }
    }

    int maxdiff = 0;
    ll sumdiff = 0;

    for(int i = 0; i < 10000; i++) {
        int best = -1;
        for(int j = 0; j <= i; j++) {
            if(poss[i][j]) {
                best = j;
            }
        }
        sumdiff += i - best;
        maxdiff = max(maxdiff, i - best);
        if(i - best == 25) {
            cout << "i : " << i << " best j : " << best << '\n';
            cout << "prime factors of i : " << getprimes(i) << " prime factors of j : " << getprimes(best) << '\n';

        }
    }

    cout << "maxdiff : " << maxdiff << '\n';
    cout << "sumdiff : " << sumdiff << '\n';

    // map<int,int> dists;
    // ll squaresums = 0;
    // for(int i = 1; i < prime.size(); i++) {
    //     dists[prime[i] - prime[i-1]]++;
    //     squaresums += (prime[i] - prime[i-1]) * (prime[i] - prime[i-1]);
    // }

    // cout << "dists : " << dists << '\n';
    // cout << "ss : " << squaresums << '\n';

    // int casi; cin >> casi;
    // while(casi-->0) solve();

    return 0;
}