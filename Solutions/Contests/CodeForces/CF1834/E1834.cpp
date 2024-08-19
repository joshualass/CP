#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//missed basic observation

void solve() {
    ll n; cin >> n;
    vector<ll> poss(n * 2 + 1);
    vector<ll> cur;
    for(ll i = 0; i < n; i++) {
        ll a; cin >> a;
        
        vector<ll> next;
        if(a <= n * 2) {
            poss[a] = 1;
            next.push_back(a);
            for(ll x : cur) {
                ll g = a * x / gcd(a,x);
                if(g != next.back()) {
                    if(g <= n * 2) {
                        next.push_back(g);
                        poss[g] = 1;
                    }
                }
            }
        }
        cur = next;
    }
    for(ll i = 1; i <= n * 2; i++) {
        if(!poss[i]) {
            cout << i << '\n';
            return;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    // cerr << "ok\n";

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
// const ll N = 6e5 + 1;

// ll prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
// vector <ll> prime;

// void sieve (ll n = N) {
// 	std::fill (prime_factor, prime_factor + n, -1);
// 	for (ll i = 2; i < n; ++i) {
// 		if (prime_factor[i] == -1) {
// 		    prime.push_back(i);
//             prime_factor[i] = i;
//         }
// 		for (ll j = 0; j < prime.size () && i * prime[j] < n; ++j) {
// 			prime_factor[i * prime[j]] = prime[j];
// 			if (i % prime[j] == 0) break;
// 		}
// 	}
// }


// void solve() {

//     ll n; cin >> n;

//     vector<ll> b(n);
//     vector<stack<array<ll,2>>> stks(2 * n + 1); //idx, cnt}
//     ll lastclear = -1;
//     vector<vector<ll>> use(n);

//     for(ll i = 0; i < n; i++) {
//         cin >> b[i];
//         ll a = b[i];
//         if(a > n * 2) {
//             lastclear = i;
//         } else {
//             map<ll,ll> factors;
//             factors[1] = 1;
//             while(a != 1) {
//                 factors[prime_factor[a]]++;
//                 a /= prime_factor[a];
//             }
//             ll minuse = i;
//             for(auto [div, cnt] : factors) {
//                 while(stks[div].size() && cnt > stks[div].top()[1]) {
//                     stks[div].pop();
//                 }
//                 if(stks[div].size()) {
//                     minuse = min(minuse, stks[div].top()[0] + 1);
//                 } else {
//                     minuse = lastclear + 1;
//                 }
//                 stks[div].push({i,cnt});
//             }
//             minuse = max(minuse, lastclear + 1);
//             use[minuse].push_back(i);
//         }
//     }

//     // cout << "use\n";
//     // for(ll i = 0; i < n; i++) {
//     //     cout << "i : " << i << " use[i] : " << use[i] << '\n';
//     // }

//     vector<ll> poss(n * 2 + 1);
//     set<ll> s;
//     for(ll i = 0; i < n; i++) {
//         for(ll x : use[i]) {
//             s.insert(x);
//         }
//         ll g = 1;
//         set<ll>::iterator it = s.lower_bound(i);
//         while(it != s.end()) {
//             ll x = *it;
//             g = g * b[x] / gcd(g,b[x]);
//             if(g > n * 2) break;
//             // cout << "i : " << i << " g : " << g << '\n';
//             poss[g] = 1;
//             it++;
//         }
//     }

//     for(ll i = 1; i <= n * 2; i++) {
//         if(poss[i] == 0) {
//             cout << i << '\n';
//             return;
//         }
//     }
//     assert(0);
//     cout << "-1\n";
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     sieve();
//     ll casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }