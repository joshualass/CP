#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()
const ll inf = 1e18;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = -inf;
    vector<T> v;
    ll n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a, b);
    }
    Tree(vector<T> a) {
        this->n = sz(a); //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        for(ll i = 0; i < n; i++) {
            v[i + size] = a[i];
        }
        for(ll i = size - 1; i >= 1; i--) {
            v[i] = f(v[i * 2], v[i * 2 + 1]);
        }
    }
    void update(ll pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        ll curr = pos + size;
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
    T at(ll idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(ll l, ll r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(ll idx, ll currl, ll currr, ll &targetl, ll &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        ll mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
    bool isLeaf(ll idx) {
        return idx >= size;
    }
    bool cond(T query_val, T tree_node) {
        return tree_node < query_val;
    }
    pair<ll,T> find_first(ll l, ll r, T query_val) {
        return _find_first(1, 0, size, l, r, query_val);
    }
    pair<ll,T> _find_first(ll idx, ll cl, ll cr, ll tl, ll tr, T qv) {
        // cout << "idx : " << idx << " cl : " << cl << " cr : " << cr << " tl : " << tl << " tr : " << tr << "\n";
        if(cr <= tl || cl >= tr) return {n, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            ll mid = (cl + cr) / 2;
            auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
            if(p.first != n){
                return p;
            }
            return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
        } else {
            return {n, base};
        }
    }
};

/*
general find first logic
just like a query, make sure there is some overlap
then see if there is anything good in llerval to keep pursuing
if so, see if done if leaf else, try the greedy sides. 
*/

//TODO check that range properly works with tl and tr. only tested for tl = 0 and tr = n. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<ll> a(n), c(n);
    for(ll &x : a) cin >> x;
    for(ll &x : c) cin >> x;

    ll asum = accumulate(a.begin(), a.end(), 0LL), csum = accumulate(c.begin(), c.end(), 0LL);

    a.reserve(n * 2);
    a.insert(a.end(), a.begin(), a.end());
    c.reserve(n * 2);
    c.insert(c.end(), c.begin(), c.end());

    vector<ll> p(n * 2 + 1), pa(n * 2 + 1);

    for(ll i = 0; i < n * 2; i++) {
        if(i) p[i] = p[i-1];
        p[i] -= a[i];
        if(i) {
            p[i] += c[i-1];
        }
        pa[i + 1] = pa[i] + a[i];
    }

    // cout << "p : " << p << endl;

    // cout << "pa : " << pa << endl;

    auto can_go = [&](ll coin, ll start, ll step) -> ll {
        ll cost = 0;
        ll go = min(n - start, step);
        cost += pa[start + go] - pa[start];
        step -= go;
        cost += pa[step];
        // cout << "coin : " << coin << " start : " << start << " step : " << step << " cost : " << cost << endl;
        return cost <= coin;
    };

    ll res = 0;
    Tree<ll> tree(p);

    for(ll i = 0; i < n; i++) {

        auto [idx, _] = tree.find_first(i, i + n, p[i]);

        // cout << "i : " << i << " idx : " << idx << " val : " << _ << endl;

        if(idx != n * 2 + 1) {
            res = max(res, idx - i);
        } else {
            ll cycles = csum / asum;
            ll coin = csum - cycles * asum;
            ll l = 0, r = n;
            while(l != r) {
                ll m = (l + r + 1) / 2;
                if(can_go(coin, (i + 1) % n, m)) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            // cout << "cycles : " << cycles << " coin : " << coin << " l : " << l << endl;
            res = max(res, cycles * n + l + 1);
        }
    }

    cout << res << '\n';

    return 0;
}
