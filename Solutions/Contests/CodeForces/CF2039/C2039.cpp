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

void find_divs(int idx, int p, vector<pair<int,int>> &facts, vector<int> &nums) {
    if(idx == facts.size()) {
        nums.push_back(p);
        return;
    }
    for(int j = 0; j < facts[idx].second + 1; j++) {
        find_divs(idx + 1, p, facts, nums);
        p *= facts[idx].first;
    }
}

//O(sqrt(n)), approx. cuberoot(n) factors. 
void find_divisors(int num, vector<int> &nums) {
    // map<int,int> factors;
    vector<pair<int,int>> factors;
    // cout << "num: " << num << " ";
    for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
        bool first = 1;
        while(num % prime[i] == 0) {
            if(first) {
                factors.push_back({prime[i],1});
                first = 0;
            } else {
                factors.back().second++;
            }
            num /= prime[i];
        }
    }
    if(num != 1) {
        factors.push_back({num,1});
    }
    // cout << factors << "\n";
    find_divs(0, 1, factors, nums);
}

void solve() {
    // ll x, m; cin >> x >> m;
    // int res = 0;
    // for(ll y = 1; y <= min(m, x * 4); y++) {
    //     if(x != y) {
    //         if(x != y && (x%(x^y)==0)||(y%(x^y)==0)) {
    //             // cout << "ok y : " << y << '\n';
    //             res++;
    //         }
    //     }
    // }
    // cout << res << '\n';
    // vector<int> divs;
    // find_divisors(x,divs);
    // int res = 0;
    // for(int div : divs) {
    //     if((x ^ div) <= m && (x ^ div) != 0) {
    //         res++;
    //     }
    // }
    // cout << res << '\n';

    ll x, m; cin >> x >> m;
    if(m <= x * 4) {
        int res = 0;
        for(int i = 1; i <= m; i++) {
            int z = (x ^ i);
            if((z % x == 0) || (i && z % i == 0)) {
                res++;
            }
        }
        cout << res << '\n';
    } else {
        ll res = m / x;
        for(ll i = 0; i < x; i++) {
            ll t = m - i;
            if((t^x) > m) {
                res -= (t % x == 0);
                res += ((t^x) % x == 0);
            }
        }
        for(int i = 1; i <= x * 4; i++) {
            int t = (i ^ x);
            if(t % x && t % i == 0) {
                res++;
            }
        }
        cout << res << '\n';
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