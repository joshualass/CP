#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
moral of the story - do not hardcode things, just do forloops and make things nice. 
*/

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

/*
down = 0, up = 1, right = 2, left = 3
*/


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, h, w; cin >> n >> h >> w;
    string s; cin >> s;

    auto get_pos_cnt = [&](int mxdown, int mxup, int mxright, int mxleft, int nxdir) -> int {
        //nxdir == 0 means up/down
        //nxdir == 1 means right/left

        //alr max in some direction
        if(mxdown - mxup >= h || mxright - mxleft >= w) return 0; 

        //this should be opposite. 
        if(nxdir == 0) {
            return w - (mxright - mxleft);
        } else {
            return h - (mxdown - mxup);
        }

    };

    int mxdown = 0, mxup = 0, mxright = 0, mxleft = 0;

    int cr = 0, cc = 0;

    Z res = 0;
    ll pos_left = 1LL * h * w;

    for(int i = 0; i < s.size(); i++) {
        char c = s[i];
        ll pos_cnt = 0;
        if(c == 'D') {
            cr++;
            if(cr > mxdown) {
                pos_cnt = get_pos_cnt(mxdown, mxup, mxright, mxleft, 0);
                mxdown = cr;
            }
        } else if(c == 'U') {
            cr--;
            if(cr < mxup) {
                pos_cnt = get_pos_cnt(mxdown, mxup, mxright, mxleft, 0);
                mxup = cr;
            }
        } else if(c == 'R') {
            cc++;
            if(cc > mxright) {
                pos_cnt = get_pos_cnt(mxdown, mxup, mxright, mxleft, 1);
                mxright = cc;
            }
        } else if(c == 'L') {
            cc--;
            if(cc < mxleft) {
                pos_cnt = get_pos_cnt(mxdown, mxup, mxright, mxleft, 1);
                mxleft = cc;
            }
        }
        // cout << "i : " << i << " pos_cnt : " << pos_cnt << '\n';
        pos_left -= pos_cnt;
        res += (i + 1) * pos_cnt;
    }

    if(pos_left && cc == 0 && cr == 0) {
        cout << "-1\n";
        return 0;
    }

    int ncr = 0, ncc = 0;
    int cmxdown = 0, cmxup = 0, cmxright = 0, cmxleft = 0;

    vector<array<int,3>> discover_times;

    for(int i = 0; i < n; i++) {
        char c = s[i];
        ll pos_cnt = 0;
        if(c == 'D') {
            ncr++;
            if(ncr > cmxdown) {
                cmxdown = ncr;
                if(ncr + cr > mxdown) {
                    discover_times.push_back({0, ncr, i});
                }
            }
        } else if(c == 'U') {
            ncr--;
            if(ncr < cmxup) {
                cmxup = ncr;
                if(ncr + cr < mxup) {
                    discover_times.push_back({1, ncr, i});
                }
            }
        } else if(c == 'R') {
            ncc++;
            if(ncc > cmxright) {
                cmxright = ncc;
                if(ncc + cc > mxright) {
                    discover_times.push_back({2, ncc, i});
                }
            }
        } else if(c == 'L') {
            ncc--;
            if(ncc < cmxleft) {
                cmxleft = ncc;
                if(ncc + cc < mxleft) {
                    discover_times.push_back({3, ncc, i});
                }
            }
        }
    }

    int cycle = 1;

    // cout << "discover times : " << discover_times << '\n';

    // cout << "cr : " << cr << " cc : " << cc << '\n';
    // cout << "mxright : " << mxright << " mxleft : " << mxleft << " mxdown : " << mxdown << " mxup : " << mxup << '\n';

    // cout << "pos_left : " << pos_left << '\n';

    while(pos_left) {
        // cout << "cycle : " << cycle << " pos_left : " << pos_left << '\n';
        assert(pos_left > 0);
        for(auto [dir, c, t] : discover_times) {
            ll pos_cnt = 0;
            if(dir == 0) {
                pos_cnt = get_pos_cnt(mxdown, mxup, mxright, mxleft, 0);
                assert(mxdown + 1 == cycle * cr + c);
                mxdown = cycle * cr + c;
            } else if(dir == 1) {
                pos_cnt = get_pos_cnt(mxdown, mxup, mxright, mxleft, 0);
                assert(mxup - 1 == cycle * cr + c);
                mxup = cycle * cr + c;
            } else if(dir == 2) {
                pos_cnt = get_pos_cnt(mxdown, mxup, mxright, mxleft, 1);
                assert(mxright + 1 == cycle * cc + c);
                mxright = cycle * cc + c;
            } else if(dir == 3) {
                pos_cnt = get_pos_cnt(mxdown, mxup, mxright, mxleft, 1);
                assert(mxleft - 1 == cycle * cc + c);
                mxleft = cycle * cc + c;
            }
            Z turn = 1LL * cycle * n + t + 1;
            res += turn * pos_cnt;
            // assert(pos_cnt);
            pos_left -= pos_cnt;
        }
        cycle++;
    }

    cout << res << '\n';

    return 0;
}
