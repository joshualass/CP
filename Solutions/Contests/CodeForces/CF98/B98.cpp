#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// const ll X = 1e9;
 
// struct Bigint {
//     int n, op;
//     ll a[1005];
    
//     Bigint() { n = op = 0; }
    
//     Bigint(int x) {
//         n = 0;
//         if(x < 0) op = -1, x = -x;
//         else if(x > 0) op = 1;
//         else op = 0, a[0] = 0;
//         while(x) {
//             a[n++] = x % X;
//             x /= X;
//         }
//     }
    
//     Bigint(const Bigint &x) {
//         op = x.op, n = x.n;
//         for(int i = 0; i < n; i++) a[i] = x.a[i];
//     }
    
//     void resize(int len) {
//         n = len;
//         for(int i = 0; i < n; i++) a[i] = 0;
//     }
    
//     bool operator==(const Bigint& t) const {
//         if(n != t.n) return 0;
//         for(int i = n-1; i >= 0; i--)
//             if(a[i] != t.a[i])
//                 return 0;
//         return 1;
//     }
    
//     bool operator<(const Bigint& t) const {
//         if(n != t.n) return n < t.n;
//         for(int i = n-1; i >= 0; i--)
//             if(a[i] != t.a[i])
//                 return a[i] < t.a[i];
//         return 0;
//     }
    
//     void init() {
//         ll res = 0;
//         for(int i = 0; i < n; i++) {
//             a[i] += res;
//             ll tmp = ((a[i]) % X + X) % X;
//             res = (a[i] - tmp) / X;
//             a[i] = tmp;
//         }
//         if(!res) {
//             while(n && !a[n-1]) n--;
//             return;
//         }
//         if(res < 0) return;
//         while(res) {
//             a[n++] = res % X;
//             res /= X;
//         }
//     }
    
//     Bigint move(int k) const {
//         Bigint tmp;
//         tmp.resize(n + k);
//         for(int i = 0; i < n; i++) tmp.a[i + k] = a[i];
//         return tmp;
//     }
    
//     Bigint split(int l, int r) const {
//         Bigint tmp;
//         tmp.resize(r - l + 1);
//         for(int i = 0; i < tmp.n; i++) tmp.a[i] = a[l + i];
//         return tmp;
//     }
    
//     Bigint operator+(const Bigint& t) const {
//         Bigint tmp;
//         tmp.resize(max(n, t.n));
//         for(int i = 0; i < tmp.n; i++) {
//             if(i < n) tmp.a[i] += a[i];
//             if(i < t.n) tmp.a[i] += t.a[i];
//         }
//         tmp.init();
//         return tmp;
//     }
    
//     Bigint operator-(const Bigint& t) const {
//         Bigint tmp;
//         tmp.resize(max(n, t.n));
//         for(int i = 0; i < tmp.n; i++) {
//             if(i < n) tmp.a[i] += a[i];
//             if(i < t.n) tmp.a[i] -= t.a[i];
//         }
//         tmp.init();
//         return tmp;
//     }
    
//     Bigint operator*(const Bigint& t) const {
//         Bigint tmp;
//         tmp.resize(n + t.n);
//         for(int i = 0; i < n; i++) {
//             for(int j = 0; j < t.n; j++) {
//                 tmp.a[i + j] += a[i] * t.a[j];
//                 tmp.a[i + j + 1] += tmp.a[i + j] / X;
//                 tmp.a[i + j] %= X;
//             }
//         }
//         tmp.init();
//         return tmp;
//     }
    
//     Bigint operator/(const Bigint& t) const {
//         Bigint tmp, x = (*this);
//         tmp.resize(n);
//         for(int i = n-1; i >= 0; i--) {
//             Bigint tt = t.move(i);
//             int l = 0, r = X-1;
//             while(l <= r) {
//                 int mid = (l + r) >> 1;
//                 if(x < tt * Bigint(mid)) r = mid-1;
//                 else tmp.a[i] = mid, l = mid+1;
//             }
//             x = x - tt * tmp.a[i];
//         }
//         tmp.init();
//         return tmp;
//     }
    
//     Bigint operator%(const Bigint& t) const {
//         Bigint x = (*this);
//         for(int i = n-1; i >= 0; i--) {
//             Bigint tt = t.move(i);
//             int l = 0, r = X-1, id = 0;
//             while(l <= r) {
//                 int mid = (l + r) >> 1;
//                 if(x < tt * Bigint(mid)) r = mid-1;
//                 else id = mid, l = mid+1;
//             }
//             x = x - tt * id;
//         }
//         x.init();
//         return x;
//     }
    
//     bool operator<(int x) const { return (*this) < Bigint(x); }
//     bool operator==(int x) const { return (*this) == Bigint(x); }
//     Bigint operator+(int x) const { return (*this) + Bigint(x); }
//     Bigint operator-(int x) const { return (*this) - Bigint(x); }
    
//     Bigint operator*(int x) const {
//         if(x >= X) return (*this) * Bigint(x);
//         Bigint tmp;
//         tmp.resize(n + 1);
//         ll sum = 0;
//         for(int i = 0; i < n; i++) 
//             sum += a[i] * x, tmp.a[i] = sum % X, sum /= X;
//         tmp.a[n] = sum;
//         tmp.init();
//         return tmp;
//     }
    
//     Bigint operator/(int x) const {
//         if(x >= X) return (*this) / Bigint(x);
//         Bigint tmp;
//         tmp.resize(n);
//         ll sum = 0;
//         for(int i = n-1; i >= 0; i--) 
//             sum = sum * X + a[i], tmp.a[i] = sum / x, sum %= x;
//         tmp.init();
//         return tmp;
//     }
    
//     Bigint operator%(int x) const {
//         if(x >= X) return (*this) % Bigint(x);
//         ll sum = 0;
//         for(int i = n-1; i >= 0; i--) 
//             sum = (sum * X + a[i]) % x;
//         return Bigint(sum);
//     }
    
//     void print() const {
//         if(!n) { 
//             putchar('0'); 
//             return; 
//         }
//         printf("%lld", (long long)a[n-1]);
//         for(int i = n-2; i >= 0; i--) 
//             printf("%09lld", (long long)a[i]);  // Print exactly 9 digits, pad with zeros
//     }
// };
 
// Bigint gcd(Bigint x, Bigint y) {
//     int cnt = 0;
//     if(y < x) swap(x, y);
//     while(!(x == Bigint(0))) {
//         while(!(x.a[0] & 1) && !(y.a[0] & 1)) {
//             x = x / 2, y = y / 2;
//             cnt++;
//         }
//         while(!(x.a[0] & 1)) x = x / 2;
//         while(!(y.a[0] & 1)) y = y / 2;
//         if(y < x) swap(x, y);
//         y = y - x;
//     }
//     while(cnt--) y = y * 2;
//     return y;
// }

// struct frac {
//     Bigint n, d; 
//     frac(Bigint n, Bigint d) {
//         Bigint g = gcd(n, d);
//         this->n = n / g;
//         this->d = d / g;
//     }
// };

// frac operator+(frac lhs, frac rhs) {
//     return frac(lhs.n * rhs.d + lhs.d * rhs.n, lhs.d * rhs.d);
// }

// frac operator*(frac lhs, frac rhs) {
//     return frac(lhs.n * rhs.n, lhs.d * rhs.d);
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     int t = __builtin_ctz(n);
//     frac o(t, 1);
//     n >>= t;

//     frac p(1,1); // probability of making it this far in the tree
//     frac r(0,1); // res 


//     if(n != 1) {
//         Bigint l = 1;
        
//         do {
//             Bigint f = 0;
//             while(l < n) {
//                 f = f + 1;
//                 l = l * 2;
//             }

//             // cout << "n : " << n << " l : " << l << " f : " << f << '\n';
//             // cout << "p : " << p.n << "/" << p.d << '\n';
//             // cout << "f : " << f << '\n';

//             r = r + p * frac(f, 1);

//             // cout << "upd r : " << r.n << "/" << r.d << '\n';

//             Bigint bad = l - n;

//             p = p * frac(bad, l);       
//             l = bad;

//         } while(!(l == 1));

//         // cout << "final r : " << r.n << "/" << r.d << '\n';

//         // cout << "final p : " << p.n << "/" << p.d << '\n';

//         frac left = frac(1,1) + frac(-1, p.d);

//         // cout << "left p : " << left.n << "/" << left.d << '\n';

//         frac res = frac(r.n * left.d, r.d * left.n);

//         // cout << "res : " << res.n << "/" << res.d << '\n';

//         res = res + o;

//         res.n.print();
//         cout << "/";
//         res.d.print();

//         // cout << res.n << "/" << res.d << '\n';
//     } else {

//         // cout << o.n << "/" << o.d << '\n';
//         o.n.print();
//         cout << "/";
//         o.d.print();
//     }


//     // int res = 0;
//     // int n; cin >> n;
//     // for(int i = 1; i <= n; i++) {
//     //     int t = i;
//     //     while(t % 2 == 0) t /= 2;
//     //     if(t == 1) continue;

//     //     // cout << "i : " << i << endl;

//     //     int c = 2;
//     //     int o = 0;
//     //     while(c != 1) {
//     //         o++;
//     //         c = c * 2 % t;
//     //     }
//     //     res = max(res, o);
//     //     // cout << "ok\n";
//     // }

//     // cout << "res : " << res << endl;

//     // int n; cin >> n;

//     // vector<frac> dp(n + 1);

//     // dp[0] = frac(0, 1);
//     // dp[1] = frac(0, 1);

//     // for(int i = 2; i <= n; i++) {
//     //     ll a = 1;
//     //     while(i > 1 << a) a++;

//     //     ll groups_left = (1 << a) - i;
//     //     frac hit(i, 1 << a), miss(groups_left, 1 << a);

//     //     ll size_pg = (i + groups_left - 1) / groups_left;

//     //     frac decide_left_ops = dp[size_pg];

//     //     ll extra = size_pg * groups_left - i;




//     // }

//     return 0;
// }


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// current solution is not quite optimal because we need to somehow use 
// the information for how we fail; not just reset anew.

// suppose we fail with 5
// there is a 5/8 chance of ok
// then there is a 3/8 chance of failing
// 1/8 chance failing after 3 flips and 1/4 chance failing after 2 flips
// 1/3 chance for one way and 2/3 for the other way. how can we use this info ?

// maybe try next largest group that fits



// */

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << "/";
//         }
//     }
//     return os;
// }

// array<ll,2> add(array<ll,2> a, array<ll,2> b) {
//     array<ll,2> res = {a[0] * b[1] + a[1] * b[0], a[1] * b[1]};
//     ll g = gcd(res[0], res[1]);
//     res[0] /= g;
//     res[1] /= g;
//     return res;
// }

// array<ll,2> sub(array<ll,2> a, array<ll,2> b) {
//     array<ll,2> res = {a[0] * b[1] - a[1] * b[0], a[1] * b[1]};
//     ll g = gcd(res[0], res[1]);
//     res[0] /= g;
//     res[1] /= g;
//     return res;
// }

// array<ll,2> mul(array<ll,2> a, array<ll,2> b) {
//     array<ll,2> res = {a[0] * b[0], a[1] * b[1]};
//     ll g = gcd(res[0], res[1]);
//     res[0] /= g;
//     res[1] /= g;
//     return res; 
// }

// array<ll,2> lo(array<ll,2> a, array<ll,2> b) {
//     if(a[0] * b[1] < b[0] * a[1]) {
//         return a;
//     } else {
//         return b;
//     }
// }

// array<ll,2> pc[10001];

// /*
// *************************************
// need to build sieve --> sieve() 
// *************************************
// */
// const int N = 1e6 + 1;

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

// void find_divs(int idx, int p, vector<pair<ll,int>> &facts, vector<int> &nums) {
//     if(idx == facts.size()) {
//         nums.push_back(p);
//         return;
//     }
//     for(int j = 0; j < facts[idx].second + 1; j++) {
//         find_divs(idx + 1, p, facts, nums);
//         p *= facts[idx].first;
//     }
// }

// void prime_factorize(ll num, vector<pair<ll,int>> &prime_factors) {
//     for(int i = 0; i < prime.size() && 1ll * prime[i] * prime[i] <= num; i++) {
//         if(num % prime[i] == 0) {
//             prime_factors.push_back({prime[i],0});
//             while(num % prime[i] == 0) {
//                 prime_factors.back().second++;
//                 num /= prime[i];
//             }
//         }
//         while(num < N && num != 1) {
//             int t = prime_factor[num];
//             prime_factors.push_back({t, 0});
//             while(num % t == 0) {
//                 prime_factors.back().second++;
//                 num /= t;
//             }
//         }
//     }
//     if(num != 1) {
//         prime_factors.push_back({num,1});
//     }
// }

// //O(sqrt(n)), approx. cuberoot(n) factors. 
// void find_divisors(int num, vector<int> &nums) {
//     vector<pair<ll,int>> prime_factors;
//     prime_factorize(num, prime_factors);
//     find_divs(0, 1, prime_factors, nums);
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NUll);

//     sieve();

//     auto get_flips = [](int n) -> array<ll,2> {
//         int flips = ceil(log2(n));
//         int a = 1 << flips;

//         array<ll,2> lhs = {1,1};
//         array<ll,2> rhs = mul(array<ll,2>{flips,1}, array<ll,2>{n, a});

//         int left = a - n;

//         for(int i = 0; i < flips; i++) {
//             if((left >> (flips - 1 - i)) & 1) {
//                 array<ll,2> f = {1, 1 << (i + 1)};
//                 int fc = i + 1;
//                 lhs = sub(lhs, f);
//                 rhs = add(rhs, mul(f, array<ll,2>{fc, 1}));
//             }
//         }

//         array<ll,2> res = mul(rhs, array<ll,2>{lhs[1], lhs[0]});
//         return res;
//     };

//     for(int i = 1; i <= 10000; i++) {
//         pc[i] = get_flips(i);
//     }

//     int n; cin >> n;

//     for(int i = 1; i <= n; i++) {
//         cout << "i : " << i << " pc[i] : " << pc[i] << '\n';
//     }

//     vector<array<ll,2>> dp(n + 1, array<ll,2>{10000, 1});

//     for(int i = 1; i <= n; i++) {
//         vector<int> divs;
//         find_divisors(i, divs);
//         dp[i] = pc[i];
//         for(int div : divs) {
//             dp[i] = lo(dp[i], add(dp[i/div], dp[div]));
//         }
//         cout << "i : " << i << " dp[i] : " << dp[i] << " vs " << pc[i] << '\n';
//     }

//     cout << dp[n] << '\n';

//     return 0;
// }