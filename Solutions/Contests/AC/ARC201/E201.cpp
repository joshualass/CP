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

//RECENTLY MODIFIED AND COULD BE UNSTABLE. REMOVE ME WHEN THIS IS WORKING. 

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = 0; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = {0, 1}; //lazy neutral, applying this value to its node will not change its value
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //stores lazy update values
    int n, size;
    //if OJ is not up to date, remove all occurrences of ln
    Lazy(int n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
    }
    bool isLeaf(int node) {return node >= size;}
    T query_comb(T val1, T val2) {//update this depending on query type
        return val1 + val2;
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        if(val.first) {
            lazy[node] = val;
        } else {
            lazy[node].second *= val.second;
        }
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        if(lazy[node].first) {
            v[node] = lazy[node].second;
        } else {
            v[node] *= lazy[node].second;
        }
    }
    void push_lazy(int node, int size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
        }
        lazy[node] = ln;
    }
    void update(int l, int r, D val) { //[l,r)
        _update(1,0,size,l,r, val);
    }
    void _update(int node, int currl, int currr, int &targetl, int &targetr, D val) {
        if (currl >= targetr || currr <= targetl) return;
        push_lazy(node, currr - currl);
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            int mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, val);
            push_lazy(node * 2, (currr - currl) / 2);
            push_lazy(node * 2 + 1, (currr - currl) / 2);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(int l, int r) { // [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr) return qn; 
        push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
        if(currl >= targetl && currr <= targetr) { //complete overlap
            return v[node];
        } else {
            int mid = (currl + currr) / 2;
            return query_comb(
                _query(node * 2, currl, mid, targetl, targetr),
                _query(node * 2 + 1, mid, currr, targetl, targetr)
            );
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<int,2>> a(n);
    for(int i = 0; i < n; i++) {
        int y; cin >> y;
        a[i] = {i, y - 1};
    }

    Z res = 0;

    // Z totalway = Z(n - 1) * Z(n - 1) * power<Z>(2, n);
    Z totalway = Z(n - 1) * Z(n - 1) * (power<Z>(2, n) - 1);

    // Z sub_rectangle = Z(-4) * 2 * (power<Z>(2, n - 1) - 1) * (n - 1);
    Z sub_rectangle = 0;
    for(int i = 0; i < n - 1; i++) {
        sub_rectangle -= 4 * (power<Z>(2, (i + 1)) - 1) * (n - 1);
    }

    res += totalway;
    res += sub_rectangle;

    // cout << "totalway : " << totalway << '\n';
    // cout << "sub_rectangle : " << -sub_rectangle << '\n';

    auto rotate = [&]() -> void {
        for(auto &x : a) {
            swap(x[0], x[1]);
            x[0] = n - 1 - x[0];
        }
    };

    Z corner_ways = 0;

    auto work = [&]() -> void {
        Lazy<Z, pair<int,Z>> lazy(n - 1);
        for(int i = 0; i < n - 1; i++) lazy.update(i, i + 1, {1, 1});

        sort(a.begin(), a.end());

        for(int i = 0; i < n - 1; i++) {
            auto [x, y] = a[i];
            lazy.update(y, n - 1, {0, 2});
            Z delta = lazy.query(0, n - 1) - (n - 1);
            res += delta;
            // cout << "i : " << i << " y : " << y << " delta : " << delta << '\n';
        }

    };

    for(int i = 0; i < 4; i++) {
        // cout << "i : " << i << '\n';
        work();
        rotate();
    }

    res += corner_ways;
    // cout << "corner_ways : " << corner_ways << '\n';

    cout << res << '\n';

    return 0;
}
