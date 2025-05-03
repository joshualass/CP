#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

constexpr array<int,2> operator+(const array<int,2> &lhs, const array<int,2> &rhs) {
    return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
}

const int N = 1e6;
int dsu[N];
int sizes[N];
int ec[N];
int ttfang[N];

void dsubuild(int n) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
        ec[i] = 0;
        ttfang[i] = 0;
    }
}

int find(int x) {
    // cout << "find x : " << x << endl;
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    // cout << "merge x : " << x << " y : " << y << endl;
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
    ec[x] += ec[y];
    ttfang[x] += ttfang[y];
}

void add(int x) {
    // cout << "add called x : " << x << endl;
    x = find(x);
    ec[x]++;
}

void solve() {
    
    int n, m, k; cin >> n >> m >> k;
    dsubuild(n * m);
    array<int,2> p = {};
    for(auto &x : p) cin >> x, x--;
    Z res = 1;

    vector<array<int,2>> d0 = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<array<int,2>> d1 = {{1,1},{-1,1},{-1,-1},{1,-1}};

    auto get_id = [&](array<int,2> a) -> int {
        return a[0] * m + a[1];
    };

    for(int i = 0; i < k; i++) {
        array<int,2> nx = {};
        for(auto &x : nx) cin >> x, x--;
        if(abs(p[0] - nx[0]) + abs(p[1] - nx[1]) != 2) res = 0;

        for(int j = 0; j < 4; j++) {
            if(nx == p + d0[j] + d0[j]) {
                add(get_id(p + d0[j]));
                ttfang[find(get_id(p + d0[j]))] = 1;
            }
            if(nx == p + d1[j]) {
                int u = get_id(p + array<int,2>{d1[j][0], 0});
                int v = get_id(p + array<int,2>{0, d1[j][1]});
                add(u);
                merge(u, v);
            }
        }
        p = nx;
    }

    vector<int> vis(n * m);
    for(int i = 0; i < n * m; i++) {
        int x = find(i);
        if(vis[x]) continue;
        // cout << "x : " << x << endl;
        vis[x] = 1;
        if(ec[x]) {
            // cout << "ec[x] : " << ec[x] << " sz[x] : " << sizes[x] << endl;
            if(ec[x] > sizes[x]) res = 0;
            if(ec[x] < sizes[x]) res *= sizes[x];
            if(ec[x] == sizes[x] && ttfang[x] == 0) res *= 2;
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<class T>
// constexpr T power(T a, ll b) {
//     T res = 1;
//     for (; b; b /= 2, a *= a) {
//         if (b % 2) {
//             res *= a;
//         }
//     }
//     return res;
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

// constexpr int P = 1e9 + 7;
// using Z = Mint<P>;
// // using Z = double;
// const int MAXN = 1e6 + 1;
// vector<Z> fact(MAXN), inv_fact(MAXN), res(MAXN), pows(MAXN);

// Z choose(int n, int k) {
//     if(k < 0 || k > n) return 0;
//     return fact[n] * inv_fact[k] * inv_fact[n-k];
// }

// void init_fact(int n = MAXN) {
//     fact[0] = Z(1);
//     inv_fact[0] = Z(1);
//     for(int i = 1; i <= n; i++) {
//         fact[i] = fact[i-1] * i;
//     }
//     inv_fact[n] = 1 / fact[n];
//     for(int i = n - 1; i >= 1; i--) {
//         inv_fact[i] = inv_fact[i+1] * (i + 1);
//     }
// }

// /*
// init_fact()
// */

// constexpr array<int,2> operator+(const array<int,2> &lhs, const array<int,2> &rhs) {
//     return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
// }

// void solve() {
    
//     int n, m, k; cin >> n >> m >> k;
    
//     Z res = 1;
//     vector<vector<int>> adj(n * m);
//     vector<int> sl(n * m);
//     array<int,2> p = {};
//     for(auto &x : p) cin >> x, x--;

//     vector<array<int,2>> d0 = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
//     vector<array<int,2>> d1 = {{1,1},{-1,1},{-1,-1},{1,-1}};

//     auto get_id = [&](array<int,2> a) -> int {
//         return a[0] * m + a[1];
//     };

//     for(int i = 0; i < k; i++) {
//         array<int,2> nx = {};
//         for(auto &x : nx) cin >> x, x--;
//         if(abs(p[0] - nx[0]) + abs(p[1] - nx[1]) != 2) res = 0;

//         for(int j = 0; j < 4; j++) {
//             if(nx == p + d0[j] + d0[j]) {
//                 sl[get_id(p + d0[j])]++;
//             }
//             if(nx == p + d1[j]) {
//                 int u = get_id(p + array<int,2>{d1[j][0], 0});
//                 int v = get_id(p + array<int,2>{0, d1[j][1]});
//                 adj[u].push_back(v);
//                 adj[v].push_back(u);
//             }
//         }
//         p = nx;
//     }

//     vector<int> vis(n * m);

//     auto dfs = [&](auto self, int i, int p) -> array<Z,2> {
//         vis[i] = 1;
//         if(sl[i] > 1) res = 0;
//         array<Z,2> a = {1,1};
//         if(sl[i]) {
//             a[1] = 0; //cannot satisfy parent edge
//             for(int c : adj[i]) {
//                 if(c != p) {
//                     array<Z,2> ca = self(self, c, i);
//                     a[0] *= ca[1];
//                 }
//             }
//         } else { //not required to use this 
//             vector<array<Z,2>> b(adj[i].size());
//             for(int j = 0; j < adj[i].size(); j++) {
//                 int c = adj[i][j];
//                 array<Z,2> ca = {1,1};
//                 if(c != p) {
//                     array<Z,2> ca = self(self, c, i);
//                     a[1] *= ca[1];
//                 }
//                 b[j] = ca;
//             }
//             vector<Z> pre(adj[i].size()), suf(adj[i].size());
//             for(int j = 0; j < adj[i].size(); j++) {
//                 pre[j] = b[j][1];
//                 if(j) pre[j] *= pre[j-1];
//             }
//             for(int j = ((int) adj[j].size()) - 1; j >= 0; j--) {
//                 suf[j] = b[j][1];
//                 if(j + 1 != adj[j].size()) suf[j] *= suf[j+1];
//             }
//             a[0] = a[1];
//             for(int j = 0; j < adj[i].size(); j++) {
//                 if(adj[i][j] != p) {
//                     Z z = (j ? pre[j-1] : 1) * b[j][0] * (j + 1 != adj[i].size() ? suf[j+1] : 1);
//                     a[0] += z;
//                 }
//             }
//         }
//         if(p == -1) res *= a[0];
//         return a;
//     };

//     for(int i = 0; i < n * m; i++) {
//         if(sl[i] || adj[i].size() && !vis[i]) dfs(dfs, i, -1);
//     }

//     cout << res << '\n';    

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }