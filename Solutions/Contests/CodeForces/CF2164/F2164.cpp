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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l, *r;
    int idx, cnt, size, os;
    ll y;
    Node(int idx, int cnt): l(nullptr), r(nullptr), idx(idx), cnt(cnt), size(1), os(0), y(rng()) {}
};

void push(Node *cur) {
    assert(cur);
    cur->idx += cur->os;
    if(cur->l) cur->l->os += cur->os;
    if(cur->r) cur->r->os += cur->os;
    cur->os = 0;
}

void update(Node *cur) {
    assert(cur);
    cur->size = 1 + (cur->l ? cur->l->size : 0) + (cur->r ? cur->r->size : 0);
}

int sz(Node *cur) {
    return cur ? cur->size : 0;
}

void print(Node *cur) {
    if(!cur) return;
    print(cur->l);
    cout << "idx : " << cur->idx << " cnt : " << cur->cnt << endl;
    print(cur->r);
}

array<Node*, 2> split(Node *cur, int mx) {
    if(!cur) return {nullptr, nullptr};
    push(cur);
    array<Node*, 2> res;
    if(cur->idx <= mx) {
        array<Node*, 2> rhs = split(cur->r, mx);
        cur->r = rhs[0];
        res = {cur, rhs[1]};
    } else {
        array<Node*, 2> lhs = split(cur->l, mx);
        cur->l = lhs[1];
        res = {lhs[0], cur};
    }
    update(cur);
    return res;
}

Node* merge(Node *lhs, Node* rhs) {
    if(!lhs && !rhs) return nullptr;
    if(!lhs) return rhs;
    if(!rhs) return lhs;
    push(lhs);
    push(rhs);
    Node *res;
    if(lhs->y > rhs->y) {
        lhs->r = merge(lhs->r, rhs);
        res = lhs;
    } else {
        rhs->l = merge(lhs, rhs->l);
        res = rhs;
    }
    update(res);
    return res;
}

Node* query(Node *cur, int targ) {
    if(!cur) return nullptr;
    push(cur);
    if(cur->idx == targ) return cur;
    if(cur->idx < targ) return query(cur->r, targ);
    if(cur->idx > targ) return query(cur->l, targ);
    assert(0);
}

Node* insert(Node *cur, Node* toinsert) {
    assert(toinsert);
    // cout << "insert called" << endl;
    // cout << "cur" << endl;
    // print(cur);
    // cout << "toinsert" << endl;
    // print(toinsert);

    int insert_idx = toinsert->idx;
    auto [l, mr] = split(cur, insert_idx - 1);
    auto [m, r] = split(mr, insert_idx);
    // cout << "l size : " << sz(l) << endl;
    // cout << "m size : " << sz(m) << endl;
    // cout << "r size : " << sz(r) << endl;

    // cout << "lpart" << endl;
    // print(l);
    // cout << "mpart" << endl;
    // print(m);
    // cout << "rpart" << endl;
    // print(r);

    if(m) {
        m->cnt += toinsert->cnt;
    } else {
        m = toinsert;
        // cout << "insert update m" << endl;
    }
    auto lm = merge(l, m);
    cur = merge(lm, r);
    // cout << "insert finished cur" << endl;
    return cur;
}

void small_to_large_merge(Node*& large, Node *small, set<int> &vis, Z &res) {
    if(!small) return;
    push(small);
    small_to_large_merge(large, small->l, vis, res);
    small_to_large_merge(large, small->r, vis, res);
    small->l = nullptr;
    small->r = nullptr;
    update(small);
    res *= inv_fact[small->cnt];
    if(vis.count(small->idx) == 0) {
        Node* prev = query(large, small->idx);
        if(prev) res *= inv_fact[prev->cnt];
    }
    vis.insert(small->idx);
    large = insert(large, small);
}

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> ch(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        ch[p].push_back(i);
    }

    vector<int> a(n);
    for(int &x : a) cin >> x;

    Z res = 1;

    // auto dfs = [&](auto self, int i) -> vector<int> {
    //     // cout << "i : " << i << '\n';
    //     vector<vector<int>> d;
    //     for(int c : ch[i]) {
    //         d.push_back(self(self, c));
    //     }
        
    //     vector<int> s;
    //     for(auto b : d) {
    //         for(int i = 0; i < b.size(); i++) {
    //             while(s.size() <= i) s.push_back(0);
    //             s[i] += b[i];
    //             res *= inv_fact[b[i]];
    //         }
    //     }

    //     // cout << "s : " << s << endl;
        
    //     for(int i = 0; i < s.size(); i++) {
    //         res *= fact[s[i]];
    //     }

    //     // cout << "a[i] : " << a[i] << endl;

    //     while(s.size() <= a[i]) s.push_back(0);
    //     s[a[i]]++;
    //     if(s.size() > a[i] + 1) {
    //         int r = s[a[i] + 1];
    //         s[a[i]] += r;
    //         s.erase(s.begin() + a[i] + 1);
    //     }
    //     cout << "i : " << i << " returning" << endl;
    //     cout << s << '\n';
    //     return s;
    // };

    auto dfs = [&](auto self, int i) -> Node* {
        if(ch[i].empty()) {
            Node* cur = new Node(a[i], 1);
            // cout << "returning i " << i << endl;
            // print(cur);
            return cur;
        }
        int mx_idx = -1, mx_size = -1;
        vector<Node*> d;
        for(int c : ch[i]) {
            d.push_back(self(self, c));
            if(d.back()->size > mx_size) {
                mx_idx = d.size() - 1;
                mx_size = d.back()->size;
            }
        }
        Node *cur = d[mx_idx];
        set<int> vis;
        for(int i = 0; i < d.size(); i++) {
            if(i != mx_idx) {
                small_to_large_merge(cur, d[i], vis, res);
            }
        }

        // cout << "i : " << i << endl;
        // cout << "after small to large" << endl;
        // print(cur);

        for(int x : vis) {
            Node* node = query(cur, x);
            assert(node);
            res *= fact[node->cnt];
        }

        cur = insert(cur, new Node(a[i], 1));

        // cout << "i : " << i << endl;
        // cout << "printing dfs of everything before shift" << endl;
        // print(cur);

        //subtract all nodes with idx > a[i]
        auto [l, mr] = split(cur, a[i] - 1);
        auto [m, r] = split(mr, a[i]);
        if(r) r->os--;
        r = insert(r, m);
        cur = merge(l, r);
        // cout << "returning i : " << i << endl;
        // print(cur);
        return cur;
    };

    dfs(dfs, 0);

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