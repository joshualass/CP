#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
casework with some magic
good practice with pie and stuff

139487

*/

int no_change(vector<int> a, int m) {
    for(int i = 1; i < a.size(); i++) if(a[i] != a[i-1]) return 0;
    return 1;
}

int diff_1(vector<int> a, int m) {
    if(no_change(a, m)) return 0;
    for(int i = 0; i < a.size(); i++) {
        for(int j = i + 1; j < a.size(); j++) {
            if(__builtin_popcount(a[i] ^ a[j]) >= 2) return 0;
        }
    }
    return 1;
}

int near_base(vector<int> a, int m) {
    for(int tb = 0; tb < 1 << m; tb++) {
        int ok = 1;
        for(int j : a) if(__builtin_popcount(tb ^ j) >= 2) ok = 0;
        if(ok) return 1;
    }
    return 0;
}

int target(vector<int> a, int m) {
    for(int i = 0; i < a.size(); i++) {
        for(int j = i + 1; j < a.size(); j++) {
            if(a[i] == a[j]) return 0;
        }
    }

    for(int tb = 0; tb < 1 << m; tb++) {
        int ok = 1;
        for(int j : a) if(__builtin_popcount(tb ^ j) != 1) ok = 0;
        if(ok) return 1;
    }
    return 0;
}

int check(vector<int> &a) {
    for(int i : a) for(int j : a) if(__builtin_popcount(i ^ j) > 2) return 0;
    return 1;
}

int bf(int n, int m) {
    int res = 0;
    for(ll i = 0; i < 1 << (n * m); i++) {
        vector<int> a;
        int ok = 1;
        for(int j = 0; j < n; j++) {
            int val = (i >> (j * m)) & ((1 << m) - 1);
            for(int x : a) if(__builtin_popcount(val ^ x) > 2) {
                ok = 0;
                break;
            }
            a.push_back((i >> (j * m)) & ((1 << m) - 1));
        }
        if(ok) res++;
    }
    return res;
}

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
// using Z = double;
const int MAXN = 1e6;
Z fact[MAXN + 1], inv_fact[MAXN + 1];

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
init_fact()
*/

//RECENTLY MODIFIED AND COULD BE UNSTABLE. REMOVE ME WHEN THIS IS WORKING. 

Z choose_slow(ll n, ll k) {
    if(k < 0 || k > n) return 0;
    Z res = 1;
    for(int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

void solve() {
    
    ll n, m; cin >> n >> m;

    Z res = 0;

    //given that there are dist distinct #'s and we need all of them and no more, counts the ways
    auto get_ways_0 = [&](int dist) -> Z {
        Z ans = 0;
        for(int i = dist; i >= 1; i--) {
            Z mul = (dist - i) & 1 ? -1 : 1;
            ans += power<Z>(i, n) * choose_slow(dist, i) * mul;
        }
        return ans;
    };

    //case all same
    Z ways_choose_0_base = power<Z>(2, m) * choose_slow(m, 0);
    Z ways_choose_base_0_number = 1;
    Z ways_0 = ways_choose_0_base * ways_choose_base_0_number;

    res += ways_0;

    //case precisely m - 1 bits are the same, always
    Z ways_choose_base_1 = power<Z>(2, m - 1) * choose_slow(m, 1);
    Z ways_choose_base_1_number = get_ways_0(2);
    Z ways_1 = ways_choose_base_1 * ways_choose_base_1_number;

    res += ways_1;

    //case precisely m - 2 bits are the same, always
    Z ways_choose_base_2 = power<Z>(2, m - 2) * choose_slow(m, 2);
    Z ways_choose_base_2_number = power<Z>(4, n) - 4 * ways_choose_base_1_number - 4;
    Z ways_2 = ways_choose_base_2 * ways_choose_base_2_number;
    
    res += ways_2;

    int mul = 0;

    //case all #'s differ by 1 bit from the base
    if(m >= 3) {
        Z ways_diff_1_base_tot = power<Z>(2, m) * (power<Z>(m + 1, n));
        Z ways_diff_base_2 = power<Z>(2, m) * choose_slow(m, 2);
        Z ways_diff_base_2_number = power<Z>(3, n) - (power<Z>(2, n) - 2) * 2 - 3;
        Z magic = (power<Z>(4, n) - choose_slow(4, 3) * power<Z>(3, n) + choose_slow(4, 2) * power<Z>(2, n) - choose_slow(4, 1)) / 12 * (m - 2);
        Z sub_2 = ways_diff_base_2 * (ways_diff_base_2_number - magic);
        Z sub_1 = power<Z>(2, m) * m * (power<Z>(2, n) - 2);
        Z sub_0 = power<Z>(2, m) * (m + 1);

        // cout << "tot : " << ways_diff_1_base_tot << '\n';
        // cout << "sub_0 : " << sub_0 << '\n';
        // cout << "sub_1 : " << sub_1 << '\n';
        // cout << "2 base : " << ways_diff_base_2 << '\n';
        // cout << "2 # : " << ways_diff_base_2_number << '\n';
        // cout << "sub_2 : " << sub_2 << '\n';

        Z ways_diff = ways_diff_1_base_tot - sub_2 - sub_1 - sub_0;

        res += ways_diff;
        mul = ways_diff_base_2.x;
    }

    //other 3 case with allowing 4 candidates
    // if(m >= 3) {
    //     Z special_setups = power<Z>(2, m - 3) * choose_slow(m, 3) * 2;
    //     Z special_number = get_ways_0(4) + get_ways_0(3) * 4;
    //     Z ways_special = special_setups * special_number;

    //     // res += ways_special;
    // }  

    cout << res << '\n';

    // vector<vector<int>> ttfang = bf(n, m);
    // int checker = bf(n, m);
    // int cnt0 = 0, cnt1 = 0, nb = 0, targ = 0, checker = 0;
    // for(auto x : ttfang) {
    //     if(no_change(x, m)) cnt0++;
    //     if(diff_1(x, m)) cnt1++;
    //     if(near_base(x, m)) nb++;
    //     if(target(x, m)) targ++;
    //     if(check(x)) checker++;
    // } 

    // cout << "\nCHECK OUTPUT\n";
    // cout << "cnt0 : " << cnt0 << '\n';
    // cout << "we got : " << ways_0 << '\n';
    // cout << "cnt1 : " << cnt1 << '\n';
    // cout << "we got " << ways_1 << '\n';
    // cout << "nb : " << nb << '\n';
    // cout << "target : " << targ << '\n';

    // cout << "solution : " << checker << '\n';

    // cout << "n : " << n << " m : " << m << "\n";

    // cout << "diff : " << checker - res.x << '\n';
    // cout << "mul : " << mul << " ttfang : " << (checker - res.x) / mul << '\n';

}

// void solve() {
//     ll n, m; cin >> n >> m;

//     Z res = 0;

//     if(m == 2) {
//         res = power<Z>(4, n);
//     } else {

//     }

// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}