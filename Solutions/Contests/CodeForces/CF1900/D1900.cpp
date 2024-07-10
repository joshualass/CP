#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//copy jiangly's solution for practice
//the phi function kind of auto includes the subtraction, 

const int N = 1e5;
vector<int> divs[N+1];
int phi[N + 1];

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    ll res = 0;
    array<int,N+1> f{};
    for(int i = 0; i < n; i++) {
        for(int d : divs[a[i]]) {
            res += 1LL * phi[d] * f[d] * (n - 1 - i);
            f[d]++;
        }
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            divs[j].push_back(i);
        }
    }

    for(int i = 1; i <= N; i++) {
        phi[i] = i;
    }

    for(int i = 1; i <= N; i++) {
        for(int j = i * 2; j <= N; j += i) {
            phi[j] -= phi[i];
        }
    }

    // for(int i = 1; i <= 100; i++) {
    //     cout << "i : " << i << " phi[i] : " << phi[i] << '\n';
    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// /*
// *************************************
// need to build sieve --> sieve() 
// *************************************
// */
// const int N = 1e5 + 1;

// int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
// vector <int> prime;
// vector<int> divspc[N];

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

// void find_divs(int idx, int p, vector<pair<int,int>> &facts, vector<int> &nums) {
//     if(idx == facts.size()) {
//         nums.push_back(p);
//         return;
//     }
//     for(int j = 0; j < facts[idx].second + 1; j++) {
//         find_divs(idx + 1, p, facts, nums);
//         p *= facts[idx].first;
//     }
// }

// //O(sqrt(n)), approx. cuberoot(n) factors. 
// void find_divisors(int num, vector<int> &nums) {
//     // map<int,int> factors;
//     vector<pair<int,int>> factors;
//     // cout << "num: " << num << " ";
//     for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
//         bool first = 1;
//         while(num % prime[i] == 0) {
//             if(first) {
//                 factors.push_back({prime[i],1});
//                 first = 0;
//             } else {
//                 factors.back().second++;
//             }
//             num /= prime[i];
//         }
//     }
//     if(num != 1) {
//         factors.push_back({num,1});
//     }
//     // cout << factors << "\n";
//     find_divs(0, 1, factors, nums);
// }

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// struct chash {
//     static uint64_t splitmix64(uint64_t x) {
//         // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }
//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };
// template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
// template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

// void solve() {
//     int n; cin >> n;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;

//     sort(a.begin(), a.end());
//     vector<ll> cnts(N);

//     for(int i = 0; i < n; i++) {
//         int uses = n - i - 1;
//         for(int x : divspc[a[i]]) {
//             cnts[x] += uses;
//         }
//     }

//     ll res = 0;

//     for(int i = 0; i < n; i++) {
//         int uses = n - i - 1;
//         for(int x : divspc[a[i]]) {
//             cnts[x] -= uses;
//         }

//         pb_map<int,ll> m;
//         for(int j = divspc[a[i]].size() - 1; j >= 0; j--) {
//             ll f = divspc[a[i]][j];
//             ll cnt = cnts[f] - m[f];

//             // cout << "f : " << f << " cnt : " << cnt << '\n';

//             res += f * cnt;
//             for(int x : divspc[f]) {
//                 m[x] += cnt;
//             }
//         }
//         // cout << "after i : " << i << " res : " << res << '\n';
//     }

//     cout << res << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     sieve();
//     for(int i = 1; i < N; i++) {
//         find_divisors(i, divspc[i]);
//         sort(divspc[i].begin(), divspc[i].end());
//     }

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }