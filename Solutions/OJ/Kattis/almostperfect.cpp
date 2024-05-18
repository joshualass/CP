#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
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

void find_divs(map<int,int>::iterator it, int p, map<int,int> &facts, set<int> &nums) {
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

void find_divisors(int num, set<int> &nums) {
    map<int,int> factors;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();
    
    ll n; cin >> n;
    while(!cin.eof()) {

        set<int> nums;
        find_divisors(n,nums);
        ll sum = 0;
        for(ll num : nums) {
            sum += num;
        }
        // cout << "n : " << n << " set : " << nums << '\n';
        sum++;
        sum -= n;
        if(n == sum) {
            cout << n << " perfect\n";
        } else if(abs(n - sum) <= 2) {
            cout << n << " almost perfect\n";
        } else {
            cout << n << " not perfect\n";
        }
        cin >> n;
    }

    return 0;
}