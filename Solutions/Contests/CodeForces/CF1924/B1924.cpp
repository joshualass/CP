#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//tips to help implement for next time - it's okay to do casework. practice more ...

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    // for(auto &x : v) os << x << " ";
    // return os;
    for(int i = 1; v.size() >= 1 << i; i++) {
        for(int j = 1 << (i - 1); 1 << i > j; j++) {
            // os << "i : " << i << " j : " << j << ' ';
            os << v[j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n = 0, T def = base) {
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
            if(curr & 1) { //non
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q; cin >> n >> m >> q;
    vector<ll> X(m);
    vector<ll> V(m);

    map<ll,ll> h;

    for(ll &y : X) {
        cin >> y;
        y--;
    }
    for(ll &y : V) cin >> y;

    for(int i = 0; i < m; i++) {
        h[X[i]] = V[i];       
    }

    Tree<ll> tree(n);

    for(auto [x,v] : h) {
        //upd prev
        if(x != 0) {
            ll pi = (*--h.lower_bound(x)).first;
            tree.update(pi, (x-pi) * (x-pi-1) / 2 * h[pi]);
        }
        if(x != n - 1) {
            ll ai = (*h.upper_bound(x)).first;
            tree.update(x, (ai-x) * (ai-x-1) / 2 * v);
        }
    }

    // cout << "tree : " << tree.v;

    // cout << "h : " << h;

    for(int i = 0; i < q; i++) {
        ll t; cin >> t;
        if(t == 1) {
            ll x, v; cin >> x >> v;
            x--;
            ll pi = (*--h.lower_bound(x)).first;
            tree.update(pi, (x-pi) * (x-pi-1) / 2 * h[pi]);
            ll ai = (*h.upper_bound(x)).first;
            tree.update(x, (ai-x) * (ai-x-1) / 2 * v);
            h.insert({x,v});
        }
        if(t == 2) {
            ll l, r; cin >> l >> r;
            l--; r--; //[l,r]
            ll pi = (*h.lower_bound(l)).first;
            ll ai = (*h.lower_bound(r)).first;
            ll ans = tree.query(pi,ai);
            // cout << "l : " << l << " r : " << r << " pi : " << pi << " ai : " << ai << " ans : " << ans << '\n';
            if(pi != l) {
                // cout << "addl : " << (pi - l) * (pi - l + 1) / 2 * (*--h.lower_bound(l)).second << " bozo : " << (*--h.lower_bound(l)).second << '\n';
                ans += (pi - l) * (pi - l + 1) / 2 * (*--h.lower_bound(l)).second;//add total distance left endpoint is left of pi
            }
            if(ai != r) {
                // cout << "subr : " << (ai - r) * (ai - r - 1) / 2 * (*--h.lower_bound(r)).second << '\n';
                ans -= (ai - r) * (ai - r - 1) / 2 * (*--h.lower_bound(r)).second;
            }
            cout << ans << '\n';
        }
    }    

    return 0;
}