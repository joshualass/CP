#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstring>
typedef long long ll;
typedef long double ld;
using namespace std;
const int inf = 1e9;

/*
Notes:
Pretty obvious that we want some sort of segment tree to solve this

Things to make this implementation easier
First, we don't need to store the indices + ranges of everything, just need to store how many vacant cells to the left and to the right
Second, we don't need to store the ways for each node, just calculate this at the end. 
Third, after realizing the second observation, get ways could be greatly simplified. 
Fourth, this will be done better in the future. 

*/

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

array<Z, 2> pc[MAXN + 1];
Z tw[MAXN + 1];

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

    tw[0] = 1;
    pc[0][0] = 1;

    for(int i = 1; i <= n; i++) {
        pc[i][0] = tw[i - 1];
        pc[i][1] = pc[i-1][0];
        tw[i] = pc[i][0] + pc[i][1];
    }

}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

/*
init_fact()
*/

Z _get_ways(int len, int need) {
    return choose(len - (need - 1), need);
}

//len - length that we are appending, need - precise # of coffee needed inf means not fixed. 
//any coffees at the beginning do contribute to need
vector<vector<Z>> get_ways(int len, int need) {
    vector<vector<Z>> res(2, vector<Z>(2));
    assert(len >= 0);
    if(need == inf) {
        if(len == 0) {
            res = {
                {1, 0},
                {0, 1}
            };
        } else {
            res[0][0] = tw[len - 1]; //we fix that there is tea at the end
            if(len == 1) {
                res[0][1] = 1;
                res[1][0] = 1;
                res[1][1] = 0;
            } else {
                res[0][1] = tw[len - 2];
                res[1][0] = tw[len - 2];
                if(len == 2) {
                    res[1][1] = 1;
                } else {
                    res[1][1] = tw[len - 3];
                }
            }
        }
    } else {
        if(len == 0) {
            if(need == 0) {
                res = {
                    {1, 0},
                    {0, 1}
                };
            }
        } else {
            res[0][0] = _get_ways(len - 1, need);
            if(len == 1) {
                if(need == 0) {
                    res[1][0] = 1;
                } else if(need == 1) {
                    res[0][1] = 1;
                }
            } else {
                res[0][1] = _get_ways(len - 2, need - 1);
                res[1][0] = _get_ways(len - 2, need);
                if(len == 2) {
                    if(need == 1) {
                        res[1][1] = 1;
                    } else {
                        res[1][1] = 0;
                    }
                } else {
                    res[1][1] = _get_ways(len - 3, need - 1);
                }
            }
        }
    }
    return res;
}

vector<vector<Z>> mul(vector<vector<Z>> lhs, vector<vector<Z>> rhs) {
    vector<vector<Z>> res(2, vector<Z>(2));
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                res[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return res;
}

struct Info {
    //# of empty before and after the known elements. 
    int l, r, lhsn, rhsn;
    vector<vector<Z>> mat;
    //assume a length 0 object here. 
    Info(): l(0), r(0), lhsn(-1), rhsn(-1) {
        mat = {
            {1, 0},
            {0, 1}
        };
    }
    Info(int l, int r, int lhsn, int rhsn, vector<vector<Z>> mat): l(l), r(r), lhsn(lhsn), rhsn(rhsn), mat(mat) {}
};

std::ostream& operator<<(ostream& os, Info info) {
    os << "l : " << info.l << " r : " << info.r << " lhsn : " << info.lhsn << " rhsn : " << info.rhsn << '\n';
    os << "mat\n" << info.mat << '\n';
    return os;
}

Info operator+(Info &lhs, Info &rhs) {
    Info res;
    //if they are both empty
    if(lhs.lhsn == -1 && rhs.lhsn == -1) {
        res.l = lhs.l + rhs.l;
    } else if(lhs.lhsn == -1) { //left is empty, but right is not empty
        res.l = lhs.l + lhs.r + rhs.l;
        res.r = rhs.r;
        res.lhsn = rhs.lhsn;
        res.rhsn = rhs.rhsn;
        res.mat = rhs.mat;
    } else if(rhs.lhsn == -1) { //right is empty, but left is not empty
        res.l = lhs.l;
        res.r = lhs.r + rhs.l + rhs.r;
        res.lhsn = lhs.lhsn;
        res.rhsn = lhs.rhsn;
        res.mat = lhs.mat;
    } else {
        res.l = lhs.l;
        res.r = rhs.r;
        res.lhsn = lhs.lhsn;
        res.rhsn = rhs.rhsn;
        res.mat = mul(mul(lhs.mat, get_ways(lhs.r + rhs.l + 1, rhs.lhsn - lhs.rhsn)), rhs.mat);
    }
    return res;
}

struct Tree {
    typedef Info T;
    T base = Info();
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n, T def) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    Z query() {
        Info info = v[1];
        // cout << "info for query\n" << info;
        if(info.lhsn == -1) {
            return tw[n];
        } else {
            auto first = get_ways(info.l + 1, info.lhsn);
            // cout << "first\n" << first << '\n';
            auto second = info.mat;
            // cout << "second\n" << second << '\n';
            auto third = get_ways(info.r, inf);
            // cout << "third\n" << third << '\n';
            auto mat = mul(mul(first, second), third);
            Z res = 0;
            for(int i = 0; i < 2; i++) {
                res += mat[0][i];
            }

            // cout << "linfo\n" << v[2] << '\n';
            // cout << "rinfo\n" << v[3] << '\n';

            // cout << "llinfo\n" << v[4] << '\n';
            // cout << "lrinfo\n" << v[5] << '\n';

            return res;
        }

    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int n, q; cin >> n >> q;
    Tree tree(n, Info());

    vector<vector<Z>> mat = {
        {1, 0},
        {0, 1}
    };

    for(int i = 0; i < n; i++) {
        tree.update(i, Info(1, 0, -1, -1, mat));
    }

    for(int qq = 0; qq < q; qq++) {
        int x, y; cin >> x >> y;
        x--;
        if(y == -1) {
            tree.update(x, Info(1, 0, -1, -1, mat));
        } else {
            tree.update(x, Info(0, 0, y, y, mat));
        }
        cout << tree.query() << '\n';
    }


    return 0;
}
