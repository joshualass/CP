#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
the power of the upsolve. maybe got some ideas after solving this problem - https://atcoder.jp/contests/arc197/tasks/arc197_c
main observations that were gained were that you can start things on the primes, then do dp to see which states are reachable. 

if the starting prime is small, then start it very low to avoid doing things incorrectly. 

*/

//need to build sieve, typically with N
const int N = ((int) 2e7) + 1;

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

int dp[400][400];

void solve() {

    memset(dp, 0, sizeof(dp));

    ll n, m, l, f; cin >> n >> m >> l >> f;

    ll sn = *--upper_bound(prime.begin(), prime.end(), n);
    ll sm = *--upper_bound(prime.begin(), prime.end(), m);

    // cout << "sn : " << sn << " sm : " << sm << '\n';

    if(sn <= 350) sn = 1;
    if(sm <= 350) sm = 1;

    // if(sn == sm) {
    //     ll tn = *--lower_bound(prime.begin(), prime.end(), sn);
    //     ll tm = *--lower_bound(prime.begin(), prime.end(), sm);
    //     dp[sn-tn][0] = 1;
    //     dp[0][sm-tm] = 1;
    //     sn = tn;
    //     sm = tm;
    // } else {
    //     dp[0][0] = 1;
    // }

    ll tn = *--lower_bound(prime.begin(), prime.end(), sn);
    ll tm = *--lower_bound(prime.begin(), prime.end(), sm);
    if(tn != tm) {
        dp[0][0] = 1;
    }
    if(tn != sm) {
        dp[0][sm-tm] = 1;
    }
    if(sn != tm) {
        dp[sn-tn][0] = 1;
    } else if(sn != sm) {
        dp[sn-tn][sm-tm] = 1;
    }

    sn = tn;
    sm = tm;

    ll res = 0;

    for(int i = sn; i <= n; i++) {
        for(int j = sm; j <= m; j++) {
            if(dp[i - sn][j - sm] == 1) {
                res = max(res, i * l + j * f);
                if(i < n && dp[i-sn+1][j-sm] == 0) {
                    if(gcd(i + 1, j) <= 1) {
                        dp[i-sn+1][j-sm] = 1;
                    } else {
                        dp[i-sn+1][j-sm] = -1;
                    }
                }
                if(j < m && dp[i-sn][j-sm+1] == 0) {
                    if(gcd(i, j + 1) <= 1) {
                        dp[i-sn][j-sm+1] = 1;
                    } else {
                        dp[i-sn][j-sm+1] = -1;
                    }
                }
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    prime.insert(prime.begin(), 0);
    prime.insert(prime.begin() + 1, 1);

    // int md = 0;
    // for(int i = 1; i < prime.size(); i++) {
    //     md = max(md, prime[i] - prime[i-1]);
    //     if(prime[i] - prime[i-1] == 180) {
    //         cout << "prime[i] : " << prime[i] << " prime[i-1] : " << prime[i-1] << '\n';
    //     }
    // }

    // cout << "md : " << md << '\n';

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
//     os << "{ ";
//     for(auto x : v) os << x << " ";
//     os << '}';
//     return os;
// }

// template<typename T, typename D>
// std::ostream& operator<<(std::ostream& os, map<T,D> m) {
//     for(auto &x: m) os << x.first << " " << x.second << " | ";
//     return os;
// }

// //need to build sieve, typically with N
// const int N = 2e7 + 1;

// int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
// vector <int> prime;

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

// vector<int> getprimes(int x) {
//     vector<int> elprimo;
//     while(x != 1 && x) {
//         elprimo.push_back(prime_factor[x]);
//         x /= prime_factor[x];
//     }
//     sort(elprimo.begin(), elprimo.end());
//     return elprimo;
// }


// void solve() {
    
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     sieve();

//     cerr << "sieve is done\n";

//     vector<vector<int>> poss(10000,vector<int>(10000));

//     for(int i = 0; i < 10000; i++) {
//         for(int j = 0; j < 10000; j++) {
//             if(i == 0 || j == 0) {
//                 poss[i][j] = 1;
//             } else {
//                 if(gcd(i,j) == 1 && (poss[i-1][j] || poss[i][j-1])) {
//                     poss[i][j] = 1;
//                 }
//             }
//         }
//     }

//     int maxdiff = 0;
//     ll sumdiff = 0;

//     for(int i = 0; i < 10000; i++) {
//         int best = -1;
//         for(int j = 0; j <= i; j++) {
//             if(poss[i][j]) {
//                 best = j;
//             }
//         }
//         sumdiff += i - best;
//         maxdiff = max(maxdiff, i - best);
//         if(i - best == 25) {
//             cout << "i : " << i << " best j : " << best << '\n';
//             cout << "prime factors of i : " << getprimes(i) << " prime factors of j : " << getprimes(best) << '\n';

//         }
//     }

//     cout << "maxdiff : " << maxdiff << '\n';
//     cout << "sumdiff : " << sumdiff << '\n';

//     // map<int,int> dists;
//     // ll squaresums = 0;
//     // for(int i = 1; i < prime.size(); i++) {
//     //     dists[prime[i] - prime[i-1]]++;
//     //     squaresums += (prime[i] - prime[i-1]) * (prime[i] - prime[i-1]);
//     // }

//     // cout << "dists : " << dists << '\n';
//     // cout << "ss : " << squaresums << '\n';

//     // int casi; cin >> casi;
//     // while(casi-->0) solve();

//     return 0;
// }