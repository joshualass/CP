#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

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

int debug = 0;

Z solve(int n, int x, int y, vector<int> a, vector<int> b) {
    
    if(!debug) {
        cin >> n >> x >> y;
        a.resize(n);
        b.resize(n);
        for(int &x : a) cin >> x;
        for(int &x : b) cin >> x;
    }

    if(x > y) {
        x = n - x;
        y = n - y;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
    } else {
        x--; 
        y--;
    }

    Z half = Z(1) / 2;
    vector<ll> p(n + 1);
    for(int i = 1; i <= n; i++) {
        p[i] = p[i-1] + (i - 1 == x || i - 1 == y ? a[i-1] : b[i-1]);
    }

    auto get_p = [&](int l, int r, int nx) -> Z {
        ll s = p[r] - p[l];
        int tot = 0;
        if(l && s >= a[l-1]) tot++;
        if(r < n && s >= a[r]) tot++;
        int pos = s >= a[nx];
        if(!pos) return 0;
        if(tot == 1) return 1;
        return half;
    };

    auto dies_here = [&](int l, int r) -> int {
        ll s = p[r] - p[l];
        if(l && s >= a[l-1]) return 0;
        if(r < n && s >= a[r]) return 0;
        return 1;
    };

    auto work = [&](int start) -> vector<vector<Z>> {
        vector<vector<Z>> dp(n + 1, vector<Z>(n)); //dp[t][i] -> probability that at time t, the leftmost fish eaten by fish at start is fish i
        dp[1][start] = 1;
        for(int time = 2; time <= n; time++) {
            for(int i = 0; i < n; i++) {
                if(i + time <= n) {
                    dp[time][i] = dp[time-1][i+1] * get_p(i + 1, i + 1 + (time - 1), i);
                    dp[time][i] += dp[time-1][i] * get_p(i, i + (time - 1), i + (time - 1));
                }
            }
        }
        return dp;
    };

    auto dpa = work(x), dpb = work(y);
    Z paeb = 0, bdt = 0;

    // cout << "dpa\n";
    // for(int time = 1; time <= n; time++) {
    //     cout << "time : " << time << " dpa[time] : " << dpa[time] << endl;
    // }

    // cout << "dpb\n";
    // for(int time = 1; time <= n; time++) {
    //     cout << "time : " << time << " dpb[time] : " << dpb[time] << endl;
    // }
    
    vector<vector<Z>> dpm(n + 1, vector<Z>(n));
    if(x + 1 == y) dpm[2][x] = 1;

    for(int time = 2; time <= n; time++) {
        for(int i = 0; i < n; i++) {
            int pxl = time / 2, pyl = (time - 1) / 2;
            if(time >= 3 && i + time <= n) {
                if(time % 2 == 1) { //alice / x eats
                    //already merged, alice eats left
                    {
                        int xl = i + 1;
                        int yl = xl + pxl;
                        ll xs = p[xl + pxl] - p[xl], ys = p[yl + pyl] - p[yl];
                        int total = (a[i] <= xs) + (xs >= ys);
                        Z d = total == 2 ? half : 1;
                        if(total) {
                            int left = a[i] <= xs, right = xs >= ys;
                            dpm[time][i] += dpm[time-1][i+1] * left * d;
                        }
                    }
                    {
                        //merge now by alice eating to the right
                        int xl = i, yl = xl + pxl + 1;
                        dpm[time][i] += dpa[pxl][xl] * get_p(xl, xl + pxl, xl + pxl) * dpb[pyl][yl];
                    }

                } else {
                    {
                        //already merged, bob eats right
                        int xl = i, yl = i + pxl;
                        int nx = i + time - 1;
                        ll xs = p[xl + pxl] - p[xl], ys = p[yl + pyl] - p[yl];
                        
                        if(a[nx] <= ys) {
                            Z prob = (ys >= xs ? half : 1);
                            dpm[time][i] += dpm[time-1][i] * prob;
                        }
                    }
                    {
                        //merge now by bob eating to the left
                        int xl = i, yl = xl + pxl + 1;
                        dpm[time][i] += dpa[pxl][xl] * get_p(yl, yl + pyl, yl - 1) * dpb[pyl][yl];
                    }
                }
            }
            if(i + time <= n && time % 2 == 0) {
                //add probability that alice eats bob's fish in the next turn 
                pyl++;
                int xl = i, yl = i + pxl;
                ll xs = p[xl + pxl] - p[xl], ys = p[yl + pyl] - p[yl];
                int n = xs >= ys;
                int total = (xs >= ys) + (i && xs >= a[i-1]);
                Z d = total == 2 ? half : 1;
                Z contrib = dpm[time][i] * n * d;
                // if(contrib) {
                    //     cout << "time : " << time << " i : " << i << " contrib : " << contrib << endl;
                    //     cout << "p : " << n * d << " dpm val : " << dpm[time][i] << endl;
                    // }
                    paeb += contrib;
            }
            if(i + time <= n && time % 2 == 1) {
                pxl++;
                int xl = i, yl = i + pxl;
                ll xs = p[xl + pxl] - p[xl], ys = p[yl + pyl] - p[yl];
                int f = 0;
                if(yl + pyl < n && ys >= a[yl + pyl]) f = 1;
                if(ys >= xs) f = 1;
                if(f == 0) {
                    bdt += dpm[time][i];
                }
            }
        }
    }

    // cout << "dpm\n";
    // for(int time = 1; time <= n; time++) {
    //     cout << "time : " << time << " dpm[time] : " << dpm[time] << endl;
    // }

    //compute probability b dies on its own before encountering alice
    vector<vector<Z>> b_die(n + 1, vector<Z>(n));
    for(int time = 1; time <= n; time++) {
        for(int j = n - 1; j >= 0; j--) {
            if(j + time <= n) {
                if(dies_here(j, j + time)) b_die[time][j] += dpb[time][j];
            }
            if(j + 1 < n) b_die[time][j] += b_die[time][j+1];
        }
    }

    Z bds = 0;

    for(int time = 2; time <= n; time++) {
        for(int i = 0; i + time + 2 <= n; i++) {
            bds += dpa[time][i] * b_die[time - 1][i + time + 1];
        }
    }

    // cout << "paeb : " << paeb << " bds : " << bds << " bdt : " << bdt << endl;
    Z res = paeb + bds + bdt;
    if(debug == 0) {
        cout << res << '\n';
    }

    return res;
}

Z solve_slow(int n, int _x, int _y, vector<int> a, vector<int> b) {

    Z res = 0;
    auto dfs = [&](auto self, int x, int y, int turn, Z p, vector<int> &a, vector<int> &b) -> void {
        assert(0 <= x && x < sz(a));
        assert(0 <= y && y < sz(b));
        int fish;
        if(turn == 0) {
            fish = x;
        } else {
            fish = y;
        }
        vector<int> eats;
        if(fish && a[fish] >= a[fish - 1]) eats.push_back(fish-1);
        if(fish + 1 < sz(a) && a[fish] >= a[fish+1]) eats.push_back(fish+1);
        if(eats.empty()) {
            if(turn == 1) res += p;
            return;
        }
        for(int to : eats) {
            if(to == y) {
                res += p / sz(eats);
            } else if(to == x) {
                continue;
            } else {
                vector<int> nxa = a, nxb = b;
                nxa[fish] += b[to];
                nxa.erase(nxa.begin() + to);
                nxb.erase(nxb.begin() + to);
                int nx = x, ny = y;
                if(to < nx) nx--;
                if(to < ny) ny--;
                self(self, nx, ny, turn ^ 1, p / sz(eats), nxa, nxb);
            }
        }
    };

    dfs(dfs, _x - 1, _y - 1, 0, 1, a, b);
    return res;
}



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    if(debug == 0) {
        while(casi-->0) solve(0, 0, 0, {}, {});
    }
    if(debug == 1) {
        while(casi-->0) {
            int n, x, y; cin >> n >> x >> y;
            vector<int> a(n), b(n);
            for(int &x : a) cin >> x;
            for(int &x : b) cin >> x;
            Z res_fast = solve(n, x, y, a, b), res_slow = solve_slow(n, x, y, a, b);
            cout << "fast : " << res_fast << " slow : " << res_slow << endl;
        }
    }
    if(debug == 2) {
        while(1) {
            int n = 5;
            int x = rng() % n + 1, y = rng() % n + 1;
            while(x == y) y = rng() % n + 1;
            vector<int> a(n), b(n);
            for(int &x : a) x = rng() % 10 + 1;
            for(int &x : b) x = rng() % 10 + 1;
            Z res_fast = solve(n, x, y, a, b), res_slow = solve_slow(n, x, y, a, b);
            // cout << "fast : " << res_fast << " slow : " << res_slow << endl;
            if(res_fast != res_slow) {
                cout << "ttfang !" << endl;
                cout << "fast : " << res_fast << " slow : " << res_slow << endl;
                cout << n << " " << x << " " << y << endl;
                for(int x : a) cout << x << " ";
                cout << endl;
                for(int x : b) cout << x << " ";
                cout << endl;
                assert(0);
            }
        }
    }

    return 0;
}