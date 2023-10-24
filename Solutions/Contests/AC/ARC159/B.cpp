#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <ll> prime;

void sieve (int n) {
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

void find_divs(map<ll,ll>::iterator it, ll p, map<ll,ll> &facts, set<ll> &nums) {
    if(it == facts.end()) {
        if(p != 1) {
            nums.insert(p);
        }
        return;
    }
    for(int j = 0; j < (*it).second + 1; j++) {
        find_divs(++it, p, facts, nums);
        --it;
        p *= (*it).first;
    }
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

void find_divisors(ll num, set<ll> &nums) {
    map<ll,ll> factors;
    // cout << "num: " << num << " ";
    for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
        while(num % prime[i] == 0) {
            factors[prime[i]]++;
            num /= prime[i];
        }
    }
    if(num != 1) {
        factors[num]++;
    }
    // cout << factors << "\n";
    find_divs(factors.begin(), 1, factors, nums);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve(N);

    ll a, b; cin >> a >> b;
    if(a > b) swap(a,b);
    if(a == b) {
        cout << "1\n";
        return 0;
    }
    ll ops = 0;
    while(a >= 1 && b >= 1) {
        ll g = gcd(a,b);
        if(g != 1) {
            a /= g;
            b /= g;
            continue;
        }
        ll diff = b - a;
        if(diff == 1) {
            ops += a;
            break;
        }
        set<ll> diff_divisors;
        find_divisors(diff,diff_divisors);
        ll closest = -1;
        ll best = -1;
        for(auto x : diff_divisors) {
            // cout << "x: " << x << "\n";
            if(a - a % x > closest) {
                closest = a - a % x;
                best = x;
            } else if(a - a % x == closest && x > best) {
                best = x;
            }
        }
        ll change = a - closest;
        // cout << "a: " << a << " b: " << b << " closest: " << closest << " best: " << best << " change: " << change << "\n";
        ops += change;
        a -= change;
        b -= change;
    }   
    cout << ops << "\n";
    return 0;
}