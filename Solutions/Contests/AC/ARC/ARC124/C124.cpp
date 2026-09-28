#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " - " << x.second << " | ";
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

map<int,int> get_prime_factors(int a) {
    map<int,int> m;
    for(auto p : prime) {
        while(a % p == 0) {
            m[p]++;
            a /= p;
        }
    }
    if(a != 1) {
        m[a]++;
    }
    return m;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int n; cin >> n;

    vector<pair<map<int,int>,map<int,int>>> v;

    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        map<int,int> first = get_prime_factors(a);
        map<int,int> second = get_prime_factors(b);
        v.push_back({first,second});
        cout << "i : " << i << " a : " << a << " first : " << first << '\n';
        cout << "i : " << i << " b : " << b << " second : " << second << '\n';
    }


    return 0;
}