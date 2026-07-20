#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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

    // vector<vector<int>> ids(n, vector<int>(m, -1));
    // vector<vector<int>> lifts;
    // vector<int> depths;

    // auto lca = [&](int a, int b) -> int {
    //     if(depths[a] < depths[b]) swap(a, b);
    //     int up = depths[a] - depths[b];
    //     for(int i = 19; i >= 0; i--) {
    //         if((up >> i) & 1) a = lifts[a][i];
    //     }
    //     for(int i = 19; i >= 0; i--) {
    //         if(lifts[a][i] != lifts[b][i]) {
    //             a = lifts[a][i];
    //             b = lifts[b][i];
    //         }
    //     }
    //     if(a != b) {
    //         a = lifts[a][0];
    //     }
    //     return a;
    // };


    // for(int i = n - 1; i >= 0; i--) {
    //     for(int j = m - 1; j >= 0; j--) {
    //         if(a[i][j] == '1') {
    //             int r = (i + 1 < n && a[i+1][j] == '1' ? ids[i+1][j] : -1);
    //             int c = (j + 1 < m && a[i][j+1] == '1' ? ids[i][j+1] : -1);
    //             if(r == -1) {
    //                 r = c;
    //             }
    //             if(c == -1) {
    //                 c = r;
    //             }
    //             if(r == -1) {
    //                 assert(i == n - 1 && j == m - 1);
    //                 depths.push_back(0);
    //                 ids[i][j] = 0;
    //                 lifts.push_back(vector<int>(20));
    //             } else {
    //                 int anc = lca(r, c);
    //                 vector<int> nx(20);
    //                 nx[0] = anc;
    //                 for(int k = 1; k < 20; k++) {
    //                     nx[k] = lifts[nx[k-1]][k-1];
    //                 }
    //                 int id = sz(depths);
    //                 ids[i][j] = id;
    //                 lifts.push_back(nx);
    //                 depths.push_back(depths[anc] + 1);
    //             }

    //             cout << "i : " << i << " j : " << j << " r : " << r << " c : " << c << " depths : " << depths.back() << endl;

    //             res += power<Z>(2, depths.back());

    //         }
    //     }
    // }

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

const int N = 1e7;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}

int dx[8]{-1, -1, -1, 0, 0, 1, 1, 1}, dy[8]{-1, 0, 1, -1, 1, -1, 0, 1};

void solve() {
    
    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<vector<int>> vis1(n, vector<int>(m)), vis2(n, vector<int>(m));

    auto visit = [&](vector<vector<int>> &v) -> void {
        v[0][0] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(v[i][j]) {
                    if(i + 1 < n && a[i+1][j] == '1') {
                        v[i+1][j] = 1;
                    }
                    if(j + 1 < m && a[i][j+1] == '1') {
                        v[i][j+1] = 1;
                    }
                }
            }
        }
    };

    visit(vis1);
    reverse(a.begin(), a.end());
    for(int i = 0; i < n; i++) reverse(a[i].begin(), a[i].end());
    visit(vis2);
    reverse(vis2.begin(), vis2.end());
    for(int i = 0; i < n; i++) reverse(vis2[i].begin(), vis2[i].end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < n; i++) reverse(a[i].begin(), a[i].end());

    int block_cnt = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(vis1[i][j] == 0 || vis2[i][j] == 0) a[i][j] = '0';
            if(a[i][j] == '0') block_cnt++;
        }
    }

    Z res = power<Z>(2, block_cnt) - 1;
    // cout << "block contrib : " << res << endl;

    a.insert(a.begin(), string(m + 2, '0'));
    for(int i = 1; i <= n; i++) {
        a[i].insert(a[i].begin(), '0');
        a[i].push_back('0');
    }

    a.push_back(string(m + 2, '0'));
    n += 2;
    m += 2;

    a[0][0] = '1';
    a[0][1] = '1';
    a[1][0] = '1';

    a[n-1][m-1] = '1';
    a[n-2][m-1] = '1';
    a[n-1][m-2] = '1';

    // cout << "a : " << a << endl;

    vector<vector<int>> g(n, vector<int>(m, -1));
    vector<vector<array<int,2>>> comps;

    int p = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] == -1 && a[i][j] == '0') {
                queue<array<int,2>> q;
                comps.push_back({});
                auto pushq = [&](int x, int y) -> void {
                    if(g[x][y] == -1) {
                        g[x][y] = p;
                        q.push({x, y});
                        comps.back().push_back({x, y});
                    }
                };
                pushq(i, j);
                while(!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    for(int dir = 0; dir < 8; dir++) {
                        int nx = x + dx[dir];
                        int ny = y + dy[dir];
                        if(nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] == '0') {
                            pushq(nx, ny);
                        }
                    }
                }
                p++;
            }
        }
    }

    // cout << "g : " << g << endl;
    // cout << "comps : " << comps << endl;

    dsubuild(n * m);
    vector<int> matching(p, -1);
    vector<int> latest(p);

    auto get = [&](int x, int y) -> int {
        return x * m + y;
    };

    vector<array<int,2>> checks = {
        {-2, 1},
        {-2, 2},
        {-1, 2}
    };

    vector<vector<array<int,2>>> here = {
        {{-1, 0}, {-1, 1}},
        {{-1, 1}},
        {{-1, 1}, {0, 1}}
    };

    for(int i = 0; i < p; i++) {
        for(auto [x, y] : comps[i]) {
            for(int j = 0; j < 3; j++) {
                int nx = x + checks[j][0], ny = y + checks[j][1];
                if(nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] == '0') {
                    for(auto [dx, dy] : here[j]) {
                        int tx = x + dx, ty = y + dy;
                        if(tx >= 0 && tx < n && ty >= 0 && ty < m && a[tx][ty] == '1') {
                            int other_g = g[nx][ny];
                            if(matching[other_g] != i) {
                                matching[other_g] = i;
                            } else {
                                merge(get(tx, ty), latest[other_g]);
                            }
                            latest[other_g] = get(tx, ty);
                        }
                    }
                }
            }
        }
    }

    for(int i = 1; i + 1 < n; i++) {
        for(int j = 1; j + 1 < m; j++) {
            if(a[i][j] == '1') {
                int c = find(get(i, j));
                int s = sizes[c];
                res += power<Z>(2, s) - 1;
                sizes[c] = 0;
                // cout << "i : " << i << " j : " << j << " size : " << s << endl;
            }
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