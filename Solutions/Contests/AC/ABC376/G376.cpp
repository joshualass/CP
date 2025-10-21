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

/*
main observation is that no matter when we choose some node, we will have to choose the nodes above it and have to 

solve slow(node)
returns the maximum subtree average and the sequence of chops used to achieve this average
the chops are in order of chopping the lowest to highest average subtree, the chops store 
the # of elements and the sum of elements chopped. 

Given the above, how can we compute the above?
We know the current value of a_i. The chops from the children are independent of each other. 

If we try the chops in forwards order, we would solve this by simulating each of the chops from lowest average to highest average,
At each step, maintaining the average value of the current subtree. Then, when the next average of the next chop is >= the 
average of the current tree, we are now decreasing our average, so we shouldn't do this chop. 

Given that the next chop will decrease this subtree's average, should we consider it for future nodes?

No - For all cases of the current parent subtree average, we should never consider chops of this type.

More formally, we will do the chops in order, but do not do a chop if the average of the subtree of the chop is >= the average of the subtree. 
Conversely, if we are working backwards, we will not do a chop if the chop is greater than or equal to. 

Ok, this problem took a long time to solve, but it is probably good to discuss how we stumbled upon the solution to help for the future. 

Define cost[i] to be the the maximum average cost of any connected subtree of node i. The next node we pick should be one with maximum cost. why?
consider two subtrees with s_1 and s_2 total sum and n_1 and n_2 nodes in subtrees. then average is s_i / a_i. Next, the added cost from 
doing subtree 1 first is a_1 * s_2 and cost of doing subtree 2 first is a_2 * s_1, we want to do the minimum cost, which corresponds to the maximum average. 
Thus, at each step, we want to select the node with maximum cost. 

Maybe this is a guess, but now, we want to compute these cost values, which its quite hard to do. The most naive way to compute the costs is to bruteforce all subtree types. 
We can think about this differently by thinking about removing nodes from the subtree, from the ground up, we choose the cheapest subtree average and chop it, then 
chop all subtrees with average < current subtree average. This works and in polynomial time, but it is inefficient, so we should try to optimize somehow. 

We can make the observation that once we decide not to make a chop, we should never conisder any of the larger chops and instead, should just consider chopping the remaining tree. 
Why - if we look at the current average of a parent tree and if we are trying to increase it, making these higher chops would not increase the average and only potentially decrease it, 
so we can ignore all of those previous larger chops. 

Now, with this observation, we can consider the chops in order from largest to smallest and if we see that we should never make this chop, we can delete it for good for a good 
amortized runtime. We use small to large merging to find the largest chop option, kind of in reverse order. 

Now, with cost[i] computed for all i, we can greedily visit nodes with the highest cost[i] that are visitable. 
I'm going to read editorial, but there was a little bit of guessing to reach this conclusion, but it's pretty cool that it works. 

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

struct frac {
    ll n, d;
    frac(): n(1), d(1) {}
    frac(ll n, ll d): n(n), d(d) {}
    bool operator<(const frac &rhs) {
        return this->n * rhs.d < rhs.n * this->d;
    }
};

bool operator<(const frac &lhs, const frac &rhs) {
    return lhs.n * rhs.d < rhs.n * lhs.d;
}

ostream& operator<<(ostream &os, const frac f) {
    os << "n : " << f.n << " d : " << f.d;
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> ch(n + 1);
    for(int i = 1; i <= n; i++) {
        int p; cin >> p;
        ch[p].push_back(i);
    }
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<priority_queue<frac>> dp(n + 1); //pq of chops on this tree, in order of highest of lowest
    vector<frac> cost(n + 1); //rational value for the cost of exploring this subtree - maximum average of the subtree. 
    vector<array<ll,2>> sums(n + 1); // {cost, subtree size}

    auto dfs = [&](auto self, int i) -> void {
        sums[i] = {a[i], 1};
        cost[i] = frac(a[i], 1);
        int mxch = -1;
        for(int c : ch[i]) {
            self(self, c);
            if(mxch == -1 || dp[c].size() > dp[mxch].size()) {
                mxch = c;
            }
            for(int j = 0; j < 2; j++) sums[i][j] += sums[c][j];
        }

        if(mxch != -1) {
            swap(dp[i], dp[mxch]);
        }
        for(int c : ch[i]) {
            while(dp[c].size()) {
                dp[i].push(dp[c].top());
                dp[c].pop();
            }
        }

        while(dp[i].size()) {
            if(!(dp[i].top() < cost[i])) {
                cost[i].n += dp[i].top().n;
                cost[i].d += dp[i].top().d;
                dp[i].pop();
            } else {
                break;
            }
        }
        dp[i].push(cost[i]);
    };

    dfs(dfs, 0);

    // for(int i = 0; i <= n; i++) {
    //     cout << "i : " << i << " cost[i] " << cost[i] << '\n';
    // }

    ll res = 0;
    priority_queue<pair<frac,int>> pq;
    pq.push({cost[0], 0});
    int op = 0;
    while(pq.size()) {
        auto [f, id] = pq.top();
        pq.pop();

        res += a[id] * op++;
        for(int c : ch[id]) {
            pq.push({cost[c], c});
        }

    }

    cout << Z(res) / Z(accumulate(a.begin(), a.end(), 0LL)) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}