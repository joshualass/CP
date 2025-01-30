#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//matrix expo. is slow. apply hockey stick idea to quickly compute sum of
// x chooose y for y <= x <= large #. y is small.  

template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

//Modular Division currently uses Little Fermat's Theorem, so won't work for nonprime p. 
template<int P>
struct Mint {
    int x;
    constexpr Mint(): x{} {}
    constexpr Mint(ll x): x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if(P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if(x < 0) {
            x += getMod();
        }
        if(x >= getMod()) { //not sure why this is needed
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    constexpr Mint operator-() const {
        Mint res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr Mint inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr Mint &operator*=(Mint rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr Mint &operator+=(Mint rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr Mint &operator-=(Mint rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr Mint &operator/=(Mint rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr Mint operator*(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Mint operator+(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Mint operator-(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Mint operator/(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
        ll v;
        is >> v;
        a = Mint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(Mint lhs, Mint rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(Mint lhs, Mint rhs) {
        return lhs.val() != rhs.val();
    }
};

constexpr int P = 998244353;
using Z = Mint<P>;
const int MAXN = 1e7 + 1;
vector<Z> fact(MAXN), inv_fact(MAXN), res(MAXN), pows(MAXN);

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

void init_fact(int n = MAXN) {
    fact[0] = Z(1);
    inv_fact[0] = Z(1);
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i;
    }
    inv_fact[n] = 1 / fact[n];
    for(int i = n - 1; i >= 1; i--) {
        inv_fact[i] = inv_fact[i+1] * (i + 1);
    }
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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << "\n";
    return os;
}

void solve() {
    int k, n; cin >> k >> n;

    auto hockey_stick = [&](ll k, ll hi_n) -> Z {
        Z res = inv_fact[k+1];
        for(int i = 1; i <= k + 1; i++) {
            res *= n + 2 - i;
        }
        if(k == 0) res -= 1;
        return res;
    };

    for(int x = 1; x <= k; x++) {
        vector<int> divs;
        find_divisors(x, divs);
        vector<map<int,Z>> dp(30);
        dp[0][1] = 1;
        for(int div : divs) {
            if(div == 1) continue;
            for(int j = dp.size() - 1; j >= 0; j--) {
                for(auto [f, c] : dp[j]) {
                    ll mul = div;
                    int k = 1;
                    while(x % (f * mul) == 0) {
                        dp[j+k][f*mul] += c * inv_fact[k];
                        k++;
                        mul *= div;
                    }
                }
            }
        }
        // cout << "x : " << x << '\n';
        // cout << "x : " << x << " dp\n" << dp << '\n';
        Z res = 0;
        for(int i = 0; i < 30; i++) {
            res += dp[i][x] * hockey_stick(i, n) * fact[i];
            // cout << "i : " << i << " dp[i][x] : " << dp[i][x] << " hockey_stick : " << hockey_stick(i,n) << " bonus mult : " << fact[i] << '\n';
        }
        cout << res << " \n"[x == k];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();
    sieve();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// also see jiangly's template
// https://codeforces.com/contest/1895/submission/231571612
// */
// template<class T>
// constexpr T power(T a, ll b, T base = 1) {
//     for (; b; b /= 2, a *= a) {
//         if (b % 2) {
//             base *= a;
//         }
//     }
//     return base;
// }

// //Modular Division currently uses Little Fermat's Theorem, so won't work for nonprime p. 
// template<int P>
// struct Mint {
//     int x;
//     constexpr Mint(): x{} {}
//     constexpr Mint(ll x): x{norm(x % getMod())} {}

//     static int Mod;
//     constexpr static int getMod() {
//         if(P > 0) {
//             return P;
//         } else {
//             return Mod;
//         }
//     }
//     constexpr static void setMod(int Mod_) {
//         Mod = Mod_;
//     }
//     constexpr int norm(int x) const {
//         if(x < 0) {
//             x += getMod();
//         }
//         if(x >= getMod()) { //not sure why this is needed
//             x -= getMod();
//         }
//         return x;
//     }
//     constexpr int val() const {
//         return x;
//     }
//     constexpr Mint operator-() const {
//         Mint res;
//         res.x = norm(getMod() - x);
//         return res;
//     }
//     constexpr Mint inv() const {
//         assert(x != 0);
//         return power(*this, getMod() - 2);
//     }
//     constexpr Mint &operator*=(Mint rhs) & {
//         x = 1LL * x * rhs.x % getMod();
//         return *this;
//     }
//     constexpr Mint &operator+=(Mint rhs) & {
//         x = norm(x + rhs.x);
//         return *this;
//     }
//     constexpr Mint &operator-=(Mint rhs) & {
//         x = norm(x - rhs.x);
//         return *this;
//     }
//     constexpr Mint &operator/=(Mint rhs) & {
//         return *this *= rhs.inv();
//     }
//     friend constexpr Mint operator*(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res *= rhs;
//         return res;
//     }
//     friend constexpr Mint operator+(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res += rhs;
//         return res;
//     }
//     friend constexpr Mint operator-(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res -= rhs;
//         return res;
//     }
//     friend constexpr Mint operator/(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res /= rhs;
//         return res;
//     }
//     friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
//         ll v;
//         is >> v;
//         a = Mint(v);
//         return is;
//     }
//     friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
//         return os << a.val();
//     }
//     friend constexpr bool operator==(Mint lhs, Mint rhs) {
//         return lhs.val() == rhs.val();
//     }
//     friend constexpr bool operator!=(Mint lhs, Mint rhs) {
//         return lhs.val() != rhs.val();
//     }
// };

// template<typename T, typename D>
// std::ostream& operator<<(std::ostream& os, map<T,D> m) {
//     for(auto &x: m) os << x.first << " " << x.second << " | ";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
//     for(auto x : adj) {
//         for(auto y : x) os << y << " ";
//         os << "\n";
//     }
//     return os;
// }

// constexpr int P = 998244353;
// using Z = Mint<P>;

// vector<Z> fact(1,1);
// vector<Z> inv_fact(1,1);

// Z choose(int n, int k) {
//     if(k < 0 || k > n) return 0;
//     while(fact.size() < n + 1) {
//         fact.push_back(fact.back() * fact.size());
//         inv_fact.push_back(1 / fact.back());
//     }
//     return fact[n] * inv_fact[k] * inv_fact[n-k];
// }

// template<typename T>
// struct Matrix {
//     static constexpr T base = 0;
//     int r, c;
//     vector<vector<T>> mat;
//     Matrix(vector<vector<T>> _mat) {
//         r = _mat.size();
//         c = _mat[0].size();
//         mat = _mat;
//     }
//     constexpr Matrix &operator+=(Matrix rhs) & {
//         assert(r == rhs.r && c == rhs.c);
//         for(int i = 0; i < r; i++) {
//             for(int j = 0; j < c; j++) {
//                 mat[i][j] += rhs.mat[i][j];
//             }
//         }
//         return *this;
//     }
//     constexpr Matrix &operator*=(Matrix rhs) & {
//         assert(c == rhs.r);
//         vector<vector<T>> res(r,vector<T>(rhs.c));
//         for(int i = 0; i < r; i++) {
//             for(int j = 0; j < rhs.c; j++) {
//                 for(int k = 0; k < c; k++) {
//                     res[i][j] += mat[i][k] * rhs.mat[k][j];
//                 }
//             }
//         }
//         c = rhs.c;
//         mat = res;
//         return *this;
//     }
//     friend constexpr Matrix operator+(Matrix lhs, Matrix rhs) {
//         Matrix res = lhs;
//         res += rhs;
//         return res;
//     }
//     friend constexpr Matrix operator*(Matrix lhs, Matrix rhs) {
//         Matrix res = lhs;
//         res *= rhs;
//         return res;
//     }
// };

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
//     for(int i = 0; i < prime.size() && 1LL * prime[i] * prime[i] <= num; i++) {
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



// vector<map<int,Z>> sparse_mat_mult_pow(vector<map<int,Z>> a, vector<map<int,Z>> b, ll p) {
//     auto sparse_mat_mult = [](vector<map<int,Z>> a, vector<map<int,Z>> b) -> vector<map<int,Z>> {
//         vector<map<int,Z>> res(a.size());
//         for(int i = 0; i < a.size(); i++) {
//             for(auto [to, ways] : a[i]) {
//                 for(auto [final_dest, ways2] : b[to]) {
//                     res[i][final_dest] += ways * ways2;
//                 }
//             }
//         }
//         return res;
//     };
//     while(p) {
//         if(p & 1) {
//             a = sparse_mat_mult(a,b);
//         }
//         p /= 2;
//         b = sparse_mat_mult(b,b);
//     }
//     return a;
// }

// void solve() {
//     int k, n; cin >> k >> n;

//     for(int x = k; x <= k; x++) {
//         map<int,int> m;
//         vector<int> divs;
//         find_divisors(x, divs);
//         vector<map<int,Z>> a(divs.size() + 1), b(divs.size() + 1);
//         for(int j = 0; j < divs.size(); j++) {
//             m[divs[j]] = j;
//         }
//         for(int j = 0; j < divs.size(); j++) {
//             for(int l = 0; l < divs.size(); l++) {
//                 if(m.count(1LL * divs[j] * divs[l])) {
//                     b[j][m[divs[j]*divs[l]]] = 1;
//                     if(divs[j] * divs[l] == x) {
//                         b[j][divs.size()] = 1;
//                     }
//                 }   
//             }
//         }

//         b[divs.size()][divs.size()] = 1;

//         a[0][0] = 1;
//         vector<map<int,Z>> res = sparse_mat_mult_pow(a, b, n);
//         cout << res[0][divs.size()] << " \n"[x == k];
//         // vector<vector<Z>> mat(divs.size() + 1, vector<Z>(divs.size() + 1));
//         // for(int j = 0; j < divs.size(); j++) {
//         //     for(int l = 0; l < divs.size(); l++) {
//         //         if(m.count(1LL * divs[j] * divs[l])) {
//         //             mat[j][m[divs[j]*divs[l]]] = 1;
//         //             if(divs[j]*divs[l] == x) {
//         //                 mat[j][divs.size()] = 1;
//         //             }
//         //         }
//         //     }
//         // }
//         // mat[divs.size()][divs.size()] = 1;
//         // vector<vector<Z>> base(divs.size() + 1, vector<Z>(divs.size() + 1));
//         // base[0][0] = 1;
//         // Matrix<Z> matz(mat), basez(base);
//         // Matrix<Z> res = power(matz, n, basez);


//         // cout << "x : " << x << '\n';
//         // cout << "a\n";
//         // for(int j = 0; j <= divs.size(); j++) {
//         //     cout << "j - " << j << " : ";
//         //     for(auto [g, gg] : a[j]) {
//         //         cout << "g : " << g << " gg : " << gg << ' ';
//         //     }
//         //     cout << '\n';
//         // }
//         // cout << "base\n" << base << '\n';
        
//         // cout << "b\n";
//         // for(int j = 0; j <= divs.size(); j++) {
//         //     cout << "j - " << j << " : ";
//         //     for(auto [g, gg] : b[j]) {
//         //         cout << "g : " << g << " gg : " << gg << ' ';
//         //     }
//         //     cout << '\n';
//         // }
//         // cout << "mat\n" << mat << '\n';

//         // cout << "x : " << x << '\n';
//         // cout << "base\n" << base << '\n';
//         // cout << "mat\n" << mat << '\n';
//         // cout << "res\n" << res.mat << '\n';
//         // cout << res.mat[0][divs.size()] << " \n"[x == k];
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     sieve();

//     // int res = 0;

//     // for(int i = 1; i <= 100000; i++) {
//     //     vector<int> nums;
//     //     find_divisors(i,nums);
//     //     res += nums.size() * nums.size();
//     // }
//     // cout << res << '\n';
//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }