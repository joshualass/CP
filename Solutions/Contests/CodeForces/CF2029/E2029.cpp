#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//need to build sieve, typically with N
const int N = 4e5 + 1;

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
    vector<int> p,np;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(prime_factor[x] == x) {
            p.push_back(x);
        } else {
            np.push_back(x);
        }
    }
    if(p.size() == 0) {
        cout << "2\n";
        return;
    }

    if(p.size() >= 2) {
        cout << "-1\n";
        return;
    }

    int pr = p[0];
    int ok = 1;

    for(int x : np) {
        int t = x;
        int min_factor = INT_MAX;
        while(x > 1) {
            min_factor = min(min_factor,prime_factor[x]);
            x /= prime_factor[x];
        }
        if(min_factor != 2) {
            t -= min_factor;
        }
        if(pr * 2 > t) {
            // cout << "t : " << t << '\n';
            ok = 0;
        }
    }

    cout << (ok ? pr : -1) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// //need to build sieve, typically with N
// const int N = 4e5 + 1;

// int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
// int hiprime[N];
// vector <int> prime;
// set<int> gen[N];

// void sieve (int n = N) {
// 	std::fill (prime_factor, prime_factor + n, -1);
// 	for (int i = 2; i < n; ++i) {
// 		if (prime_factor[i] == -1) {
// 		    prime.push_back(i);
//             prime_factor[i] = i;
//         }
// 		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
// 			prime_factor[i * prime[j]] = prime[j];
// 			if (i % prime[j] == 0) break;
// 		}
// 	}
// }

// //O(sqrt(n)), approx. cuberoot(n) factors. 
// void find_divisors(int num, vector<int> &nums) {
//     // map<int,int> factors;
//     // cout << "num: " << num << " ";
//     for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
//         bool first = 1;
//         while(num % prime[i] == 0) {
//             if(first) {
//                 nums.push_back(prime[i]);
//             }
//             num /= prime[i];
//         }
//     }
//     if(num != 1) {
//         nums.push_back(num);
//     }
// }

// void solve() {

//     int n; cin >> n;

//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     vector<int> inprimes;

//     // cout << "a : " << a << '\n';

//     for(int x : a) {
//         if(prime_factor[x] == x) {
//             inprimes.push_back(x);
//         }
//     }

//     if(inprimes.size() >= 2) {
//         cout << "-1\n";
//         return;
//     } else if(inprimes.empty()) {
//         cout << "2\n";
//         return;
//     }

//     int ok = 1;
//     for(int x : a) {
//         if(hiprime[x] >= inprimes[0] || gen[inprimes[0]].count(x)) {

//         } else {
//             ok = 0;
//         }
//     }

//     cout << (ok ? inprimes[0] : -1) << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     sieve();

//     vector<int> reachable;
//     vector<int> reachables(1001);
    

//     // cout << "prime size : " << prime.size() << '\n';

//     // for(int p : prime) {
//     //     gen[p].insert(p);
//     // }

//     // for(int i = 2; i < N; i++) {
//     //     vector<int> divs;
//     //     find_divisors(i,divs);
//     //     // cout << "divs : " << divs.size() << endl;
//     //     hiprime[i] = *max_element(divs.begin(),divs.end());
//     //     for(int div : divs) {
//     //         for(int p : gen[i-div]) {
//     //             if(hiprime[i] <= p) {
//     //                 gen[i].insert(p);
//     //             }
//     //         }
//     //     }
//     // }

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }