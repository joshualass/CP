#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll INF = 1e18;
constexpr int P = 998244353;

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

struct segtree { 
    struct tdata {
        Z sum;
        ll addval, mx, mx2, mx_cnt, mn, mn2, mn_cnt;
        tdata(): sum(), addval(), mx(-INF), mx2(-INF), mx_cnt(), mn(INF), mn2(INF), mn_cnt() {}
        tdata(ll val): sum(val), addval(), mx(val), mx2(-INF), mx_cnt(1), mn(val), mn2(INF), mn_cnt(1) {}
        tdata(tdata l, tdata r) {
            sum = l.sum + r.sum;

            mx = max(l.mx, r.mx);
            mx2 = max(l.mx2, r.mx2);
            mx_cnt = 0;
            if (l.mx == mx) mx_cnt += l.mx_cnt;
            else mx2 = max(mx2, l.mx);
            if (r.mx == mx) mx_cnt += r.mx_cnt;
            else mx2 = max(mx2, r.mx);

            mn = min(l.mn, r.mn);
            mn2 = min(l.mn2, r.mn2);
            mn_cnt = 0;
            if (l.mn == mn) mn_cnt += l.mn_cnt;
            else mn2 = min(mn2, l.mn);
            if (r.mn == mn) mn_cnt += r.mn_cnt;
            else mn2 = min(mn2, r.mn);
        }
    };
    int ln(int node) {return 2 * node;}
    int rn(int node) {return 2 * node + 1;}
    int n; vector<tdata> st;
    segtree(int n): n(n), st(4 * n) {}
    segtree(vector<ll> &arr) : segtree(arr.size()) { build(arr, 1, 0, n - 1); }
    void apply_add(int node, int start, int end, ll val) {
        if (val == 0) return;
        st[node].sum += val * (end - start + 1);
        st[node].addval += val;

        st[node].mx += val;
        if (st[node].mx2 != -INF) st[node].mx2 += val; 

        st[node].mn += val;
        if (st[node].mn2 != INF) st[node].mn2 += val; 
    }
    void apply_min(int node, int start, int end, ll val) {
        if (val >= st[node].mx) return;
        st[node].sum -= (st[node].mx - val) * st[node].mx_cnt;
        st[node].mx = val;

        if (val < st[node].mn) st[node].mn = val;
        else if (val < st[node].mn2) st[node].mn2 = val;
    }
    void apply_max(int node, int start, int end, ll val) {
        if (val <= st[node].mn) return;
        st[node].sum += (val - st[node].mn) * st[node].mn_cnt;
        st[node].mn = val;

        if (val > st[node].mx) st[node].mx = val;
        else if (val > st[node].mx2) st[node].mx2 = val;
    }
    void pull_up(int node) {
        st[node].sum = st[ln(node)].sum + st[rn(node)].sum;

        st[node].mx = max(st[ln(node)].mx, st[rn(node)].mx);
        st[node].mx2 = max(st[ln(node)].mx2, st[rn(node)].mx2);
        st[node].mx_cnt = 0;
        if (st[ln(node)].mx == st[node].mx) st[node].mx_cnt += st[ln(node)].mx_cnt;
        else st[node].mx2 = max(st[node].mx2, st[ln(node)].mx);
        if (st[rn(node)].mx == st[node].mx) st[node].mx_cnt += st[rn(node)].mx_cnt;
        else st[node].mx2 = max(st[node].mx2, st[rn(node)].mx);

        st[node].mn = min(st[ln(node)].mn, st[rn(node)].mn);
        st[node].mn2 = min(st[ln(node)].mn2, st[rn(node)].mn2);
        st[node].mn_cnt = 0;
        if (st[ln(node)].mn == st[node].mn) st[node].mn_cnt += st[ln(node)].mn_cnt;
        else st[node].mn2 = min(st[node].mn2, st[ln(node)].mn);
        if (st[rn(node)].mn == st[node].mn) st[node].mn_cnt += st[rn(node)].mn_cnt;
        else st[node].mn2 = min(st[node].mn2, st[rn(node)].mn);
    }
    void push_down(int node, int start, int end) {
        if (start == end) return;
        int mid = (start + end) / 2;
        apply_add(ln(node), start, mid, st[node].addval);
        apply_add(rn(node), mid + 1, end, st[node].addval);
        st[node].addval = 0;
        apply_min(ln(node), start, mid, st[node].mx);
        apply_min(rn(node), mid + 1, end, st[node].mx);
        apply_max(ln(node), start, mid, st[node].mn);
        apply_max(rn(node), mid + 1, end, st[node].mn);
    }
    void build(vector<ll> &arr, int node, int start, int end) {
        if (start == end) {
            st[node] = tdata(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(arr, ln(node), start, mid);
        build(arr, rn(node), mid + 1, end);
        pull_up(node);
    }
    void update_add(int node, int start, int end, int l, int r, ll val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            apply_add(node, start, end, val);
            return;
        }
        push_down(node, start, end);
        int mid = (start + end) / 2;
        update_add(ln(node), start, mid, l, r, val);
        update_add(rn(node), mid + 1, end, l, r, val);
        pull_up(node);
    }
    void update_min(int node, int start, int end, int l, int r, ll val) {
        if (r < start || end < l || st[node].mx <= val) return;
        if (l <= start && end <= r && st[node].mx2 < val) {
            apply_min(node, start, end, val);
            return;
        }
        push_down(node, start, end);
        int mid = (start + end) / 2;
        update_min(ln(node), start, mid, l, r, val);
        update_min(rn(node), mid + 1, end, l, r, val);
        pull_up(node);
    }
    void update_max(int node, int start, int end, int l, int r, ll val) {
        if (r < start || end < l || st[node].mn >= val) return;
        if (l <= start && end <= r && st[node].mn2 > val) {
            apply_max(node, start, end, val);
            return;
        }
        push_down(node, start, end);
        int mid = (start + end) / 2;
        update_max(ln(node), start, mid, l, r, val);
        update_max(rn(node), mid + 1, end, l, r, val);
        pull_up(node);
    }
    tdata query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return tdata();
        if (l <= start && end <= r) return st[node];
        push_down(node, start, end);
        int mid = (start + end) / 2;
        return tdata(query(ln(node), start, mid, l, r), query(rn(node), mid + 1, end, l, r));
    }
    void update_add(int l, int r, ll val) {update_add(1, 0, n - 1, l, r, val);}
    void update_min(int l, int r, ll val) {update_min(1, 0, n - 1, l, r, val);}
    void update_max(int l, int r, ll val) {update_max(1, 0, n - 1, l, r, val);}
    tdata query(int l, int r) {return query(1, 0, n - 1, l, r);}
};

void solve() {
    
    int n; cin >> n;
    vector<ll> start(n);
    vector<segtree> trees(2, segtree(start));

    Z res = 0;
    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        int cur = i & 1;
        int op = cur ^ 1;
        trees[cur].update_add(0, i, a);
        trees[op].update_add(0, i, -a);
        trees[op].update_max(0, i, 0);
        // ll zsum = trees[0].query(0, n - 1).sum;
        // ll osum = trees[1].query(0, n - 1).sum;
        // cout << "i : " << i << " zsum : " << zsum << " osum : " << osum << '\n';
        res += trees[0].query(0, n - 1).sum + trees[1].query(0, n - 1).sum;
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