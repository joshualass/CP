#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
BPE, i dont think the idea is too hard to come up with once the mind is clear. implementation was not the easiest
For each mex, count the number of subarrays that have atleast this mex. 
Case 1 where none of the set elements are set, we can precompute the number of arrays that have 0 to n elements equal to -1 and then used a closed formula from there
Else, there exists some elements that are smaller than our mex. We can have a fixed [l, r] interval that must be included, let's try to count the number of subarrays that include both these
elements L and R and the number of subarrays that have some cnts of -1. We can compute the left and right intervals and the number of -1 and then do a convolution to count the total number. 
we can observe that the L and R are increasing, so we can update each time we move L and R over by 1. manually instead of doing a convolution each time @soop :(
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
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

constexpr int P = 1e9 + 7;
using Z = Mint<P>;
// using Z = double;
const int MAXN = 1e6 + 1;
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
init_fact()
*/

void solve() {
    
    int n; cin >> n;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> p(n + 1);
    int lo_val = n, lo_idx = 0;
    vector<int> atidx(n,-1);

    for(int i = 0; i < n; i++) {
        p[i+1] = p[i] + (a[i] == -1);
        if(a[i] != -1) {
            if(a[i] < lo_val) {
                lo_val = a[i];
                lo_idx = i;
            }
            atidx[a[i]] = i;
        }
    }

    // cout << "p : " << p << '\n';

    vector<int> b(n + 1); //base cnts. 
    for(int l = 0; l < n; l++) {
        for(int r = l + 1; r <= n; r++) {
            b[p[r]-p[l]]++;
        }
    }

    // cout << "b : " << b << '\n';

    vector<int> lhs(n + 1), rhs(n + 1); //num subarrays of each size. 
    vector<int> ac(n + 1); //current num ways of each way, maintain ac = conv(lhs, rhs). 
    int cl = lo_idx, cr = lo_idx; //current indices of interal array [l, r)

    for(int i = lo_idx; i >= 0; i--) lhs[p[lo_idx] - p[i]]++;
    for(int i = lo_idx; i <= n; i++) rhs[p[i] - p[lo_idx]]++;

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j + i <= n; j++) {
            ac[i+j] += lhs[i] * rhs[j];
        }
    }

    auto add_left = [&]() -> void {
        int d = p[lo_idx] - p[cl];
        lhs[d]--;
        for(int i = 0; i + d <= n; i++) {
            ac[i + d] -= rhs[i];
        }
        cl--;
    };

    auto add_right = [&]() -> void {
        int d = p[cr] - p[lo_idx];
        rhs[d]--;
        for(int i = 0; i + d <= n; i++) {
            ac[i + d] -= lhs[i];
        }
        cr++;
    };

    Z res = 0;
    int sc = 0;
    for(int i = 1; i <= n; i++) {
        if(atidx[i-1] != -1) sc++;
        if(lo_val < i) {
            // cout << "exists some smaller elements\n";
            int ai = atidx[i - 1];
            if(ai != -1) {
                while(cl > ai) add_left();
                while(cr <= ai) add_right();
            }

            // cout << "i : " << i << '\n';
            // cout << "lhs : " << lhs << '\n';
            // cout << "rhs : " << rhs << '\n';
            // cout << "ac : " << ac << '\n';


            int shift = p[cr] - p[cl];

            for(int j = max(shift, i - sc); j <= n; j++) {
                Z add = fact[j] * inv_fact[j - (i - sc)] * fact[p[n] - (i - sc)] * ac[j];
                res += add;
                // cout << "i : " << i << " j : " << j << " add : " << add << '\n';
            }

        } else {
            // cout << "do not exist smaller elements\n";
            for(int j = i; j <= n; j++) {
                Z add = fact[j] * inv_fact[j - i] * fact[p[n] - i] * b[j];
                res += add;
                // cout << "i : " << i << " j : " << j << " add : " << add << '\n';
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}