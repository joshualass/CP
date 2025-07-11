#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

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

void solve() {
    
    int n; cin >> n;

    vector<int> a(n);
    for(int &x : a) cin >> x;


    map<ll,int> res;

    for(int i = 1; i < n; i++) {
        int g = gcd(a[i-1], a[i]);
        int ta = a[i-1] / g, tb = a[i] / g;

        if(ta != 1) {
            int ta = a[i-1], tb = a[i];
            for(auto [k, v] : res) {
                for(int j = 0; j < v; j++) {
                    if(ta % k == 0) ta /= k;
                }
            }
            int g = gcd(ta, tb);
            ta /= g;
            tb /= g;
        }

        vector<pair<ll,int>> pf;
        prime_factorize(ta, pf);
        map<ll,int> pvpf(pf.begin(), pf.end());

        vector<pair<ll,int>> nxpf;
        prime_factorize(tb, nxpf);
        map<ll,int> mpf(nxpf.begin(), nxpf.end());

        for(auto [k, v] : pvpf) {
            res[k] = max(res[k], v - mpf[k]);
        }
        swap(pvpf, mpf);
        // cout << "i : " << i << '\n';
        // cout << "pv : " << pvpf << '\n';
        // cout << "nx : " << mpf << '\n';
    }

    ll num = 1;
    for(auto [k, v] : res) {
        for(int i = 0; i < v; i++) num *= k;
    }

    cout << num << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}