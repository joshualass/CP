#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
1
5
1 1 1 1 1
1 1 1 0 1
1 1 1 1 0
1 0 1 1 1
1 1 0 1 1 

checks ---
setup

if two nodes have the same set of edges, then they must be on the same path and are interchangeable (exception root is not interchangeable)
then, there is the case where one if a subset of the other. this is akin to a node being in the subtree of the other
else, they are in different subtrees. if they are in different subtrees, they cannot share an edge that is no on the path from node to to their lca. 
do these checks and all g. 

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
vector<Z> fact(MAXN + 1), inv_fact(MAXN + 1);

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

void solve() {
    
    int n; cin >> n;
    vector a(n, vector<int>(n));
    vector<int> b(n);
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(int i = 0; i < n; i++) b[i] = accumulate(a[i].begin(), a[i].end(), 0);

    Z res = accumulate(a[0].begin(), a[0].end(), 0) == n;
    vector<int> vis(n), curr_path(n);
        
    auto dfs = [&](auto self) -> void {

        vector<int> on_path;
        for(int i = 0; i < n; i++) {
            int ok = 1;
            for(int j = 0; j < n; j++) {
                if(curr_path[j] && !a[i][j]) ok = 0;
            }
            if(ok) on_path.push_back(i);
        }

        sort(on_path.rbegin(), on_path.rend(), [&](const auto &lhs, const auto &rhs) {
            return b[lhs] < b[rhs];
        });

        for(int i = 0; i < on_path.size(); i++) {
            int idx = on_path[i];
            if(vis[idx] == 0) {

                for(int j = 0; j < n; j++) {
                    int is_ss = 1, iiss = 1;;
                    for(int k = 0; k < n; k++) {
                        if(a[idx][k] && !a[j][k]) is_ss = 0;
                        if(!a[idx][k] && a[j][k]) iiss = 0;
                    }
                    if(!is_ss && !iiss) {
                        // cout << "make it here ? idx : " << idx << " j : " << j << '\n';
                        // cout << "vis : " << vis << " curr_path : " << curr_path << '\n';
                        for(int k = 0; k < n; k++) {
                            if(a[idx][k] && a[j][k] && curr_path[k] == 0) {
                                // cout << "vis : " << vis << " curr_path : " << curr_path << " idx : " << idx << " j : " << j << " k : " << k << '\n';
                                res = 0;
                            }
                        }
                    }
                }

                vector<int> nx;
                for(int j = 0; j < n; j++) {
                    if(a[idx] == a[j]) {
                        nx.push_back(j);
                        assert(vis[j] == 0);
                        vis[j] = 1;
                        curr_path[j] = 1;
                    }
                }
                if(a[idx] == a[0]) {
                    res *= fact[nx.size() - 1];
                } else {
                    res *= fact[nx.size()];
                }


                
                self(self);
                for(int x : nx) curr_path[x] = 0;

            }
        }
    };

    dfs(dfs);

    if(count(vis.begin(),vis.end(), 0)) res = 0;

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