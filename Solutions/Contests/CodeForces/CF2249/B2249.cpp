#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
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

int solve_slow(int n, vector<int> a) {

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    int res = 0;
    while(1) {
        int ok = 1;
        for(int i = 0; i + 1 < n; i++) {
            int l = 0, r = 0;
            for(int j = 0; j <= i; j++) l = max(l, p[j]);
            for(int j = i + 1; j < n; j++) r = max(r, p[j]);
            if(a[i] != min(l, r)) ok = 0;
        }

        if(ok) res++;

        if(!next_permutation(p.begin(), p.end())) break;
    }
    return res;
}

int solve(int n, vector<int> a) {

    if(*max_element(a.begin(), a.end()) != n - 1) {
        return 0;
    }
    
    int ok = 2;
    int lo = n, hi = -1;

    for(int i = 0; i < n - 1; i++) {
        if(a[i] == n - 1) {
            if(lo != n && i > hi + 1) ok = 0;
            lo = min(lo, i);
            hi = i;
        }
    }

    vector<int> vis(n + 1);
    vector<int> add(n + 1);

    add[n-2] += hi - lo;

    auto visit = [&](int x) -> void {
        if(vis[x]) ok = 0;
        vis[x] = 1;
    };

    int prev = -1, val = 0;
    for(int i = 0; i < lo; i++) {
        if(a[i] != val) {
            if(a[i] < val) ok = 0;
            visit(a[i]);
            add[val] += i - prev - 1;
            prev = i;
            val = a[i];
        }
    }

    add[val] += lo - prev - 1;

    prev = n - 1, val = 0;
    for(int i = n - 2; i > hi; i--) {
        if(a[i] != val) {
            if(a[i] < val) ok = 0;
            visit(a[i]);
            add[val] += prev - i - 1;
            prev = i;
            val = a[i];
        }
    }

    add[val] += prev - hi - 1;

    Z res = ok;
    int cnt = 0;
    for(int i = n - 2; i >= 1; i--) {
        cnt += add[i];
        if(vis[i] == 0) {
            res *= cnt--;
        }
    }

    // cout << res << '\n';
    return res.x;
}

int debug = 0;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // solve_slow(6, {3, 3, 5, 5, 5});

    if(debug == 0) {
        int casi; cin >> casi;
        for(int i = 0; i < casi; i++) {
            int n; cin >> n;
            vector<int> a(n - 1);
            for(int &x : a) cin >> x;
            cout << solve(n, a) << '\n';
        }
    } else {

        auto dfs = [&](auto self, int n, vector<int> cur) -> void {
            if(sz(cur) + 1 == n) {
                int fast = solve(n, cur);
                int slow = solve_slow(n, cur);
                if(fast != slow) {
                    cout << "f : " << fast << endl;
                    cout << "s : " << slow << endl;
                    cout << n << endl;
                    cout << cur << endl;
                    assert(0);
                }
                return;
            }
            for(int i = 1; i <= n; i++) {
                cur.push_back(i);
                self(self, n, cur);
                cur.pop_back();
            }
        };

        for(int n = 2; n <= 6; n++) {
            dfs(dfs, n, {});
        }

        cout << "ALL OK" << endl;

    }


    return 0;
}