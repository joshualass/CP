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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q; cin >> n >> m >> q;
    vector<Z> cur(n);
    for(auto &x : cur) cin >> x;

    vector<int> v(m);
    vector<Z> b(m);
    vector<vector<pair<int,Z>>> a(m);
    vector<Z> deltas(m);

    for(int i = 0; i < m; i++) {
        cin >> v[i];
        v[i]--;
        int k; cin >> k;
        cin >> b[i];
        Z next = b[i];
        for(int j = 0; j < k; j++) {
            int who, mult; cin >> who >> mult;
            who--;
            a[i].push_back({who, mult});
            next += cur[who] * mult;
        }
        deltas[i] = next - cur[v[i]];
        // cout << "i : " << i << " cur : " << cur << endl;
        cur[v[i]] = next;
    }

    // cout << "final cur : " << cur << endl;

    vector<int> cnts(m);

    for(int qq = 0; qq < q; qq++) {
        int k; cin >> k;
        Z res; cin >> res;
        vector<Z> dot(n);
        Z cur_score = 0;
        for(int i = 0; i < k; i++) {
            int who, mult; cin >> who >> mult;
            who--;
            dot[who] += mult;
            cur_score += cur[who] * mult;
        }

        auto c = cur;

        for(int i = m - 1; i >= 0; i--) {
            Z start = cur_score;
            // cout << "start : " << start << endl;
            cur_score -= c[v[i]] * dot[v[i]];
            c[v[i]] -= deltas[i];
            cur_score += c[v[i]] * dot[v[i]];

            // cout << "interim score : " << cur_score << endl;

            if(cur_score == res) {
                cnts[i]++;
            }

            // cout << "i : " << i << " cur_Score : " << cur_score << endl;

            cur_score -= c[v[i]] * dot[v[i]];
            Z k = dot[v[i]];
            dot[v[i]] = 0;

            for(auto [who, mult] : a[i]) {
                cur_score -= c[who] * dot[who];
                dot[who] += k * mult;
                cur_score += c[who] * dot[who];
            }

            cur_score += b[v[i]] * k;
            Z end = cur_score;
            
            assert(start == end);
        }
    }

    vector<int> res;
    for(int i = 0; i < m; i++) {
        if(cnts[i] == q) res.push_back(i + 1);
    }
    cout << sz(res) << '\n';
    cout << res << '\n';

    return 0;
} 
