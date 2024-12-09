#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int dp[31][31][30*30+1];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(dp, 0, sizeof(dp));

    for(int row = 0; row <= 30; row++) {
        for(int col = 0; col <= 30; col++) {
            dp[row][col][row*col] = 1;
            for(int pr = 0; pr <= row - 2; pr++) {
                for(int pc = 0; pc <= col - 2; pc++) {
                    int addfixed = (row - pr) * pc + (col - pc) * pr;
                    for(int i = 0; i + addfixed <= 30*30; i++) {
                        if(dp[pr][pc][i]) {
                            dp[row][col][i+addfixed] = 1;
                        }
                    }
                }
            }
            for(int pr = 0; pr <= row - 1; pr++) {
                for(int pc = 0; pc <= col - 1; pc++) {
                    int addfixed = row * col - pr * pc;
                    for(int i = 0; i + addfixed <= 30* 30; i++) {
                        if(dp[pr][pc][i]) {
                            dp[row][col][i+addfixed] = 1;
                        }
                    }
                }
            }
        }
    }

    int n, q; cin >> n >> q;
    for(int i = 0; i < q; i++) {
        int k; cin >> k;
        // cout << "k : " << k << " val : " << (dp[n][n][k] ? "Yes" : "No") << '\n';
        cout << (dp[n][n][k] ? "Yes" : "No") << '\n';
    }

    // cout << "6 37\n";
    // for(int i = 0; i <= 36; i++) {
    //     cout << i << '\n';
    // }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;
// const ll N = 4;

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, set<T> s) {
//     for(auto &x: s) os << x << " ";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     map<array<ll,N*2>,vector<ll>> m;

//     for(ll r = 0; r < 1 << (N*N); r++) {
//         // ll i = rng() % 1LL << (N*N);
//         ll i = r;
//         array<ll,N*2> a = {};
//         for(ll j = 0; j < N; j++) {
//             for(ll k = 0; k < N; k++) {
//                 if((i >> (j * N + k)) & 1) {
//                     a[j]++;
//                     a[k+N]++;
//                 }
//             }
//         }

//         m[a];
//         m[a].push_back(i);
//         if(r % 1000000 == 0) {
//             cerr << "r : " << r << endl;
//         }

//     }

//     cerr << "make here" << endl;

//     set<ll> fixed;
//     set<ll> unfixed;

//     for(auto [a, p] : m) {
//         ll start = p[0];
//         vector<ll> f(N*N,1);
//         for(auto pp : p) {
//             for(ll i = 0; i < N*N; i++) {
//                 if(((start >> i) & 1) != ((pp >> i) & 1)) {
//                     f[i] = 0;
//                 }
//             }
//         }
//         fixed.insert(count(f.begin(),f.end(),1));
//         unfixed.insert(N*N-count(f.begin(),f.end(),1));
//         if(count(f.begin(),f.end(),1) == 10) {
//             cerr << "a for 10 : " << a << '\n';
//             cout << "start : " << start << '\n';
//             cout << "f : " << f << '\n';
//             break;
//         }
//     }

//     // cout << "fixed : " << fixed << '\n';
//     // cout << "unfixed : " << unfixed << '\n';

//     // int n, q; cin >> n >> q;
//     for(int i = 0; i <= N*N; i++) {
//         // int k; cin >> k;
//         cout << "i : " << i << " val : " << (fixed.count(i) ? "Yes" : "No") << '\n';
//         // cout << (dp[n][n][k] ? "Yes" : "No") << '\n';
//     }

//     // ll n, q; cin >> n >> q;
//     // vector<ll> ok(n*n+1);
//     // ok[n*n] = 1;

//     // for(ll l = 3; l <= n; l++) {
//     //     for(ll w = 3; w <= n; w++) {
//     //         ok[n*n-l*w] = 1;
//     //     }
//     // }

//     // for(ll l = 2; l <= n; l++) {
//     //     ok[n*n-l*l] = 1;
//     // }

//     // for(ll i = 2; i <= n - 2; i++) {
//     //     ok[n*n-i*i-(n-i)*(n-i)] = 1;
//     // }

//     // for(ll i = 0; i < q; i++) {
//     //     ll x; cin >> x;
//     //     cout << (ok[x] ? "Yes" : "No") << '\n';
//     // }

//     return 0;
// }