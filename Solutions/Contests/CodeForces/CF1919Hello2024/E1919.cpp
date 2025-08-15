#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
combo problem that took a bit of time

first approach idea failed because we included some paths that were disjoint

the correct approach worked bottom up.

we assume that pu nodes were used in the previous layer
then, we must place nodes such that pu + node_cnt = cnts[pu_idx]. There are addzz ways to do this
and there are pu locations to do this. we add the number of ways using choose formula.

then, we iterate over all possible ends of the prefix sum, if we are below the start/end, we are required to to put a node to the left and to the right

each time we add a zigzag, we are adding a hill after one of the pu locations. 
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


void solve() {
    
    int n; cin >> n;
    vector<int> cnts(n * 2 + 1);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        cnts[x+n]++;
    }

    cnts[n]++;
    Z res = 0;
    while(cnts.back() == 0) cnts.pop_back();
    reverse(cnts.begin(), cnts.end());
    int start = n;
    while(cnts.back() == 0) {
        cnts.pop_back();
        start--;    
    }
    reverse(cnts.begin(), cnts.end());

    // cout << "start : " << start << '\n';
    // cout << "cnts : " << cnts << '\n';

    auto add_ways = [&](int end) -> void {

        // Z ways = 1;
        // if(count(cnts.begin(), cnts.end(), 0)) ways = 0;

        // vector<int> need_here = cnts, push = cnts;
        // need_here[start]--;
        // push[end]--;

        // cout << "end : " << end << '\n';
        // cout << "need here : " << need_here << '\n';
        // cout << "push : " << push << '\n';

        // for(int i = 0; i < cnts.size(); i++) {
        //     int need_down = (i ? need_here[i-1] : 0);
        //     int need_up = push[i] - need_down;
        //     if(need_up && (i + 1 >= need_here.size() || need_here[i + 1] < need_up)) {
        //         ways = 0;
        //     } else {
        //         ways *= choose(need_down + need_up, need_down);
        //         need_here[i + 1] -= need_up;
        //     }
        // }

        // res += ways;

        Z ways = 1;
        int pu = 1;

        for(int i = 1; i < cnts.size(); i++) {
            int nu = 0;
            if(i <= start) nu++;
            if(i <= end) nu++;
            int addzz = cnts[i-1] - pu;
            nu += addzz;
            int add_loc = pu;
            ways *= choose(addzz + add_loc - 1, addzz);
            pu = nu;
        }
        if(pu != cnts.back()) ways = 0;

        res += ways;

    };

    for(int end = 0; end < cnts.size(); end++) add_ways(end);

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