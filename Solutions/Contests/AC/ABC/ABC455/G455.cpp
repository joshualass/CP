#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int H = 2;
const ll M = 1e9;
const int MAXN = 2e5;
int stops[MAXN];

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<class T, size_t L>
array<T, L> operator^(array<T, L> &lhs, array<T, L> &rhs) {
    array<T, L> res = {};
    for(int i = 0; i < L; i++) res[i] = lhs[i] ^ rhs[i];
    return res;
}

template<class T, size_t L>
array<T, L> operator*(array<T, L> &lhs, array<T, L> &rhs) {
    array<T, L> res = {};
    for(int i = 0; i < L; i++) res[i] = lhs[i] * rhs[i];
    return res;
}

template<class T, size_t L>
array<T, L> operator/(array<T, L> &lhs, array<T, L> &rhs) {
    array<T, L> res = {};
    for(int i = 0; i < L; i++) res[i] = lhs[i] / rhs[i];
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
    friend constexpr bool operator<(Mint lhs, Mint rhs) {
        return lhs.val() < rhs.val();
    }
};

constexpr int P = 1e9 + 7;
using Z = Mint<P>;
// using Z = double;

/*
init_fact()
*/

//balanced arrays where every element appears k times
ll solve_freq(int n, int k, vector<int> a) {

    // cout << "k : " << k << endl;
    
    auto z = [&](array<ll,H> a) -> ll {
        ll res = 0;
        for(int i = 0; i < H; i++) {
            res ^= a[i];
        }
        return res;
    };
    
    vector<vector<int>> b(n);
    for(int i = 0; i < n; i++) stops[i] = n;

    for(int i = 0; i < n; i++) {
        b[a[i]].push_back(i);
        if(sz(b[a[i]]) > k) {
            stops[b[a[i]][sz(b[a[i]]) - k - 1]] = min(stops[b[a[i]][sz(b[a[i]]) - k - 1]], i);
        }
    }

    for(int i = n - 2; i >= 0; i--) {
        stops[i] = min(stops[i], stops[i+1]);
    }

    vector<vector<array<ll, H>>> h(n);
    
    for(int i = 0; i < n; i++) {
        array<ll, H> t = {};
        for(int j = 0; j < min(sz(b[i]), k); j++) {
            h[i].push_back({});
            if(j == k - 1) {
                h[i].back() = t;
            } else {
                for(int k = 0; k < H; k++) {
                    h[i].back()[k] = rng();
                }
            }
            t = t ^ h[i].back();
        }
    }
    
    pb_map<ll, vector<int>> m;
    array<ll, H> cur = {};
    m[z(cur)].push_back(0);
    
    vector<array<ll,H>> hashes(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < sz(b[i]); j++) {
            hashes[b[i][j]] = h[i][j%sz(h[i])];
        }
    }
    
    for(int i = 0; i < n; i++) {
        cur = cur ^ hashes[i];
        m[z(cur)].push_back(i + 1);
    }

    cur = {};
    
    ll res = 0;
    for(int i = 0; i < n; i++) {
        int add = upper_bound(m[z(cur)].begin(), m[z(cur)].end(), stops[i]) - upper_bound(m[z(cur)].begin(), m[z(cur)].end(), i);
        // cout << "i : " << i << " add : " << add << endl;
        res += add;
        cur = cur ^ hashes[i];
    }

    return res;

}

ll solve_dist(int n, int k, vector<int> a) {
    // cout << "k : " << k << endl;
    // pb_map<int, pair<int,array<Z,H>>> m; // {value, {latest occurrence, hash}}
    vector<pair<int,array<Z,H>>> m(n, {-1, {}});
    int r = 0;
    vector<array<Z,H>> h(n);
    
    auto z = [&](array<Z,H> a) -> ll {
        ll res = 0;
        ll mult = 1;
        for(int i = 0; i < H; i++) {
            res += a[i].x * mult;
            mult *= M;
        }
        return res;
    };

    array<Z,H> cur = {};
    for(int i = 0; i < H; i++) cur[i] = 1;
    
    int active = 0;

    for(int l = 0; l < n; l++) {
        // cout << "l : " << l << endl;
        // cout << "cur : " << cur << endl;
        // if(l) assert(m.count(a[l-1]));
        if(l && m[a[l-1]].first == l - 1) {
            cur = cur / m[a[l-1]].second;
            // m.erase(a[l-1]);
            m[a[l-1]] = {-1, {}};
            active--;
        }
        // cout << "mih 265" << endl;
        while(r != n && (active < k || active == k && m[a[r]] != pair<int,array<Z,H>>{-1, {}})) {
            array<Z,H> hash = {};
            if(m[a[r]] == pair<int,array<Z,H>>{-1, {}}) {
                if(active == k - 1) {
                    for(int i = 0; i < H; i++) {
                        hash[i] = 1 / cur[i];
                    }
                } else {
                    for(int i = 0; i < H; i++) {
                        Z val = 0;
                        while(val.x <= 1) val = rng();
                        hash[i] = val;
                    }
                }
                cur = cur * hash;
                active++;
            } else {
                hash = m[a[r]].second;
            }
            // cout << "r : " << r << " hash : " << hash << endl;
            h[r] = hash;
            m[a[r]] = {r, hash};
            r++;
        }
        stops[l] = r;
    }

    // cout << "mih 291" << endl;

    pb_map<ll, vector<int>> p;
    cur = {};
    for(int i = 0; i < H; i++) cur[i] = 1;
    
    for(int i = 0; i < n; i++) {
        cur = cur * h[i];
        // cout << "i : " << i << " cur : " << cur << endl;
        p[z(cur)].push_back(i + 1);
    }

    // cout << "k : " << k << endl;
    // cout << "h : " << h << endl;
    // cout << "stops : ";
    // for(int i = 0; i < n; i++) cout << stops[i] << " ";
    // cout << endl;

    ll res = 0;
    cur = {};
    for(int i = 0; i < H; i++) cur[i] = 1;

    for(int i = 0; i < n; i++) {
        ll l = z(cur);
        int add = upper_bound(p[l].begin(), p[l].end(), stops[i]) - upper_bound(p[l].begin(), p[l].end(), i);
        // cout << "i : " << i << " add : " << add << endl;
        res += add;
        cur = cur * h[i];
    }

    return res;

}

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n), b(k);
    for(int &x : a) {
        cin >> x;
        x--;
    }
    for(int &x : b) cin >> x;

    for(int i = 0; i < k; i++) {
        cout << solve_freq(n, b[i], a) << " ";
        cout << solve_dist(n, b[i], a) << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 0; i < 20; i++) cout << rng() % 3 + 1 << " ";
    // cout << endl;

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}   