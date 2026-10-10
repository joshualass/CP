#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int debug = 0;

/*
big misread. again on atcoder of all places. GG

need to analyze proof on why numbers of different powers of 2 do not affect each other. this part is unclear

they use the following argument to show why 
they claim that from the final state, we can determine a unique set of buttons pressed
that is because we can unpress the buttons, one by one from least to greatest. 
*/

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
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

vector<int> shift(vector<int> a, int shift) {
    vector<int> t(a);
    for(int i = shift; i < sz(a); i++) {
        t[i] = a[i - shift] ^ a[i];
    }
    return t;
}

int solve_slow(int n, int m, vector<int> a) {
    set<vector<int>> vis;
    queue<vector<int>> q;
    vector<int> start(n);
    start[0] = 1;
    q.push(start);
    while(sz(q)) {
        auto z = q.front();
        q.pop();
        if(vis.count(z)) continue;
        vis.insert(z);
        // cout << "z : " << z << endl;
        for(int x : a) {
            // cout << "x : " << x << endl;
            vector<int> t = shift(z, x);
            q.push(t);
        }
    }
    return sz(vis);
}

set<int> get(vector<int> a) {
    set<int> first(a.begin(), a.end()), s;

    for(int x : first) {
        int ok = 1;
        int z = x;
        while(1) {
            // cout << "z : " << z << endl;
            if(s.count(z)) {
                ok = 0;
                break;
            } else {
                if(z % 2 == 0) {
                    z /= 2;
                } else {
                    break;
                }
            }
        }
        if(ok) s.insert(x);
    }
    return s;
}

vector<int> transform(int n, int m, vector<int> a) {
    auto s = get(a);
    a.clear();
    for(int x : s) {
        for(int i = 1; i * x < n; i *= 2) a.push_back(i * x);
    }
    return a;
}

int solve_slow2(int n, int m, vector<int> a) {

    a = transform(n, m, a);

    cout << "upd a : " << a << endl;

    map<vector<int>, vector<int>> res;

    for(int i = 0; i < 1 << sz(a); i++) {
        vector<int> b(n);
        b[0] = 1;
        for(int j = 0; j < sz(a); j++) {
            if((i >> j) & 1) {
                b = shift(b, a[j]);
            }
        }
        res[b].push_back(i);
    }

    for(auto [k, v] : res) {
        if(sz(v) >= 2) {
            cout << "k : " << k << " v : " << v << endl;
        }
    }

    return sz(res);

}

int solve(int n, int m, vector<int> a) {
    // auto ta = transform(n, m, a);
    // cout << "ta : " << ta << endl;
    // return power<Z>(2, sz(ta)).x;

    map<int,map<int,int>> cnts;
    for(int x : a) {
        int p = 0;
        int t = x;
        while(t % 2 == 0) {
            p++;
            t /= 2;
        }
        cnts[t][p]++;
    }

    Z res = 1;
    for(auto [k, v] : cnts) {
        int mx = 0;
        int t = k;
        while(t < n) {
            t *= 2;
            mx++;
        }
        
        map<int,Z> dp, ndp;
        dp[0] = 1;
        
        for(int i = 0; i < mx; i++) {
            ndp.clear();
            int here = v[i];
            for(auto [bonus, ways] : dp) {
                for(int i = 0; i <= min(1, here + bonus); i++) {
                    int rem = here + bonus - i;
                    int carry = rem / 2;
                    ndp[carry] += ways;
                }
            }
            swap(dp, ndp);
        }

        Z add = 0;
        for(auto [k, v] : dp) add += v;
        // cout << "k : " << k << " v : " << v << " contrib : " << add << endl;

        res *= add;
    }

    return res.x;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(debug) {
        
        if(debug == 1) {
            while(1) {
                int n, m; cin >> n >> m;
                vector<int> a(m);
                for(int &x : a) cin >> x;
        
                cout << n << " " << m << endl;
                cout << a << endl;
        
                cout << "run slow" << endl;
                int slow = solve_slow(n, m, a);
                cout << "run fast" << endl;
                int slow2 = solve_slow2(n, m, a);
                cout << "run solve" << endl;
                int fast = solve(n, m, a);
        
                cout << "slow : " << slow << " slow2 : " << slow2 << " solve : " << fast << endl;
            }
        } else {
            for(int i = 0; i < 1000; i++) {
                mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
                int n = rng() % 100 + 2, m = rng() % 6 + 1;
                vector<int> a(m);
                for(int &x : a) x = rng() % (n - 1) + 1;
                // cout << "run slow" << endl;
                // int slow = solve_slow(n, m, a);
                cout << "run fast" << endl;
                int slow2 = solve_slow2(n, m, a);
                cout << "run solve" << endl;
                int fast = solve(n, m, a);
        
                // cout << "slow : " << slow << " slow2 : " << slow2 << " solve : " << fast << endl;
                cout << " slow2 : " << slow2 << " solve : " << fast << endl;
                // if(slow != slow2 || slow != fast) {
                if(slow2 != fast) {
                    cout << n << " " << m << endl;
                    cout << a << endl;
                    assert(0);
                }
            }
            cout << "all ok grrr" << endl;
        }

    } else {

        int n, m; cin >> n >> m;
        vector<int> a(m);
        for(int &x : a) cin >> x;
    
        cout << solve(n, m, a) << '\n';
        // cout << solve_slow2(n, m, a) << endl;

        // int i = 0;
        // Z p = 1;
        // while(p != 384912) {
        //     p *= 2;
        //     i++;
        // }

        // cout << "i : " << i << endl;

    }



    return 0;
}
