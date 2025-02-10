#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
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

void find_divs(int idx, int p, vector<pair<ll,int>> &facts, vector<int> &nums) {
    if(idx == facts.size()) {
        nums.push_back(p);
        return;
    }
    for(int j = 0; j < facts[idx].second + 1; j++) {
        find_divs(idx + 1, p, facts, nums);
        p *= facts[idx].first;
    }
}

void prime_factorize(ll num, vector<pair<ll,int>> &prime_factors) {
    for(int i = 0; i < prime.size() && 1LL * prime[i] * prime[i] <= num; i++) {
        if(num % prime[i] == 0) {
            prime_factors.push_back({prime[i],0});
            while(num % prime[i] == 0) {
                prime_factors.back().second++;
                num /= prime[i];
            }
        }
        while(num < N && num != 1) {
            int t = prime_factor[num];
            prime_factors.push_back({t, 0});
            while(num % t == 0) {
                prime_factors.back().second++;
                num /= t;
            }
        }
    }
    if(num != 1) {
        prime_factors.push_back({num,1});
    }
}

//O(sqrt(n)), approx. cuberoot(n) factors. 
void find_divisors(int num, vector<int> &nums) {
    vector<pair<ll,int>> prime_factors;
    prime_factorize(num, prime_factors);
    find_divs(0, 1, prime_factors, nums);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int ok = 1;
    string a, b, c;
    if(!(cin >> a)) ok = 0;
    if(!(cin >> b)) ok = 0;
    if(!(cin >> c)) ok = 0;
    // cout << "a : " << a << "  b: " << b << " c : " << c << '\n';

    auto stoic = [&](string s) -> int {
        int alldig = 1;
        for(char c : s) if(c < '0' || c > '9') alldig = 0;
        if(s.size() && s[0] == '0') alldig = 0;
        if(!alldig || s.size() == 0 || s.size() > 10) {
            return -1;
        }
        try {
            int z = stoi(s);
            if(z >= 2 && z <= 1e9) return z;
            return -1;
        } catch(exception e) {
            return -1;
        }
        
    };

    int ia = stoic(a);
    int ib = stoic(b);
    int ic = stoic(c);

    if(cin >> a) {
        cout << 0 << '\n';
        return 0;
    }

    // cout << "ia : " << ia << " ib : " << ib << " ic : " << ic << '\n';

    sieve();
    if(ia >= 3 && ia <= 1e9 && ia % 2 == 0 && ib >= 2 && ib <= 1e9 && ic >= 2 && ic <= 1e9) {
        vector<int> nb, nc;
        find_divisors(ib,nb);
        find_divisors(ic,nc);
        cout << (nb.size() == 2 && nc.size() == 2 && ib + ic == ia) << '\n';
    } else {
        cout << "0\n";
    }

    return 0;
}