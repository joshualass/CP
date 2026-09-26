#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 998244353;
struct mint {
    ll val; //this should always be in range [0, mod)
    mint(ll _val = 0) {val = _val; if(val < 0) val = mod + (val % mod); val %= mod;}
    mint(const mint& other) {val = other.val;}
    bool operator ==(const mint& other) const {return val == other.val;}
    bool operator ==(ll other) const {return val == other;}
    bool operator !=(const mint& other) const {return val != other.val;}
    bool operator !=(ll other) const {return val != other;}
    bool operator >(const mint& other) const {return val > other.val;}
    bool operator >(ll other) const {return val > other;}
    bool operator <(const mint& other) const {return val < other.val;}
    bool operator <(ll other) const {return val < other;}
    mint& operator =(const mint& other) {val = other.val; return *this;}
    mint& operator =(ll other) {val = other; return *this;}
    mint operator +(const mint& other) const {ll ret = val + other.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint operator +(ll other) const {return *this + mint(other);}
    mint& operator +=(const mint& other) {*this = *this + other; return *this;}
    mint& operator +=(ll other) {*this = *this + other; return *this;}
    mint operator -(const mint& other) const {ll ret = val - other.val; while(ret < 0) {ret += mod;} return mint(ret);}
    mint operator -(ll other) const {return *this - mint(other);}
    mint& operator -=(const mint& other) {*this = *this - other; return *this;}
    mint& operator -=(ll other) {*this = *this - other; return *this;}
    mint operator *(const mint& other) const {return mint((val * other.val) % mod);}
    mint operator *(ll other) const {return *this * mint(other);}
    mint& operator *=(const mint& other) {*this = *this * other; return *this;}
    mint& operator *=(ll other) {*this = *this * other; return *this;}
    mint operator /(const mint& other) const {return *this * other.pow(mod - 2);}
    mint operator /(ll other) const {return *this / mint(other);}
    mint& operator /=(const mint& other) {*this = *this / other; return *this;}
    mint& operator /=(ll other) {*this = *this / other; return *this;}
    mint operator %(const mint& other) const {return mint(val % other.val);}
    mint operator %(ll other) const {return *this % mint(other);}
    mint& operator %=(const mint& other) {*this = *this % other; return *this;}
    mint& operator %=(ll other) {*this = *this % other; return *this;}

    //don't forget about fermat's little theorem, 
    //a^(m-1) % m = 1. This means that a^(p % m) % m != a^(p) % m, rather a^(p % (m-1)) % m = a^(p) % m. 
    mint pow(ll b) const {
        mint ans(1), p(val);
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }

    friend std::ostream& operator<<(std::ostream& os, const mint& m) {os << m.val; return os;}
    friend std::istream& operator>>(std::istream& is, mint& m) {is >> m.val; return is;}
    operator size_t() const {return val;}
};
bool operator ==(ll a, const mint& b) {return mint(a) == b;}
bool operator !=(ll a, const mint& b) {return mint(a) != b;}
bool operator >(ll a, const mint& b) {return mint(a) > b;}
bool operator <(ll a, const mint& b) {return mint(a) < b;}
mint operator +(ll a, const mint& b) {return mint(a) + b;}
mint operator -(ll a, const mint& b) {return mint(a) - b;}
mint operator *(ll a, const mint& b) {return mint(a) * b;}
mint operator /(ll a, const mint& b) {return mint(a) / b;}
mint operator %(ll a, const mint& b) {return mint(a) % b;}

// template <typename T>
// struct SegtreeLazy {
//     public:
//         int n;
//         T* t;    //stores product of range
//         T* d;    //lazy tree
//         bool* upd;  //marks whether or not a lazy change is here
//         T uneut, qneut;
//         function<T(T, T)> fmodify, fcombine;
//         function<T(T, T, int)> fmodifyk;

//         SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
//             uneut = updateNeutral, qneut = queryNeutral;
//             this->fmodify = fmodify;
//             this->fmodifyk = fmodifyk;
//             this->fcombine = fcombine;
//             n = 1; //raise n to nearest pow 2
//             while(n < maxSize) n <<= 1;
//             t = new T[n * 2], d = new T[n * 2];
//             upd = new bool[n * 2];
//             for(int i = 0; i < n; i++) t[i + n] = initVal;
//             build();
//         }
	
//         //modifies the range [l, r)
//         void modify(int l, int r, T val) {_modify(l, r, val, 0, n, 1);}
//         void modify(int ind, T val) {modify(ind, ind + 1, val);}
        
//         //queries the range [l, r)
//         T query(int l, int r) {return _query(l, r, 0, n, 1);}
//         T query(int ind) {return query(ind, ind + 1);}

//         void assign(vector<T>& arr) {
//             for(int i = 0; i < min(n, (int) arr.size()); i++) t[i + n] = arr[i];
//             build();
//         }
//         void build() {
//             for(int i = n - 1; i > 0; i--) t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
//             for(int i = 0; i < n * 2; i++){d[i] = uneut; upd[i] = false;}
//         }

//     private:
//         void combine(int ind, int k) {
//             if(ind >= n) return;
//             int l = ind * 2, r = ind * 2 + 1;
//             push(l, k / 2), push(r, k / 2);
//             t[ind] = fcombine(t[l], t[r]);
//         }
//         void apply(int ind, T val) {
//             upd[ind] = true;
//             d[ind] = fmodify(d[ind], val);
//         }
//         void push(int ind, int k) {
//             if(!upd[ind]) return;
//             t[ind] = fmodifyk(t[ind], d[ind], k);
//             if(ind < n) {
//                 int l = ind * 2, r = ind * 2 + 1;
//                 apply(l, d[ind]), apply(r, d[ind]);
//             }
//             upd[ind] = false;
//             d[ind] = uneut;
//         }
//         void _modify(int l, int r, T val, int tl, int tr, int ind) {
//             if(l == r) return;
//             if(upd[ind]) push(ind, tr - tl);
//             if(l == tl && r == tr) {apply(ind, val), push(ind, tr - tl); return;}
//             int mid = tl + (tr - tl) / 2;
//             if(l < mid) _modify(l, min(r, mid), val, tl, mid, ind * 2);
//             if(r > mid) _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
//             combine(ind, tr - tl);
//         }
//         T _query(int l, int r, int tl, int tr, int ind) {
//             if(l == r) return qneut;
//             if(upd[ind]) push(ind, tr - tl);
//             if(l == tl && r == tr) return t[ind];
//             int mid = tl + (tr - tl) / 2;
//             T lans = qneut, rans = qneut;
//             if(l < mid) lans = _query(l, min(r, mid), tl, mid, ind * 2);
//             if(r > mid) rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
//             return fcombine(lans, rans);
//         }
// };


typedef mint T; T idT = {}; // node type
typedef mint U; U idU = {1}; // update type
// combine segtree nodes a and b
T f(T a, T b) { 
    return a + b; 
}
// apply updates f and g (f compose g)
U g(U f, U g) { 
    return f * g;
}
// apply update f to segtree node a
T h(U f, T a) { 
    return f * a;
}

struct lztree {
    int n;
    vector<T> t;
    vector<U> d;
    lztree(int n) : n(n), t(2*n, idT), d(n, idU) {}
    void calc(ll p) { 
        t[p] = h(d[p], f(t[p * 2], t[p * 2 + 1])); 
    }
    void apply(ll p, U v) {
        t[p] = h(v, t[p]);
        if(p < n) d[p] = g(v, d[p]);
    }
    void push(ll p) {
        p += n;
        for(int s = 24; s > 0; s--) { // need tree height <= 24
            ll i = p >> s;
            if(d[i] != idU) {
                apply(i * 2, d[i]);
                apply(i * 2 + 1, d[i]);
                d[i] = idU;
            }
        }
    }
    void set(ll p, T v) { // point set arr[p] = v
        push(p);
        t[p += n] = v;
        while(p > 1) calc(p /= 2);
    }
    T get(ll p) { // return arr[p]
        push(p);
        return t[p + n];
    }
    void update(ll l, ll r, U v) { // range update [l, r) using v
        push(l), push(r - 1);
        bool cl = false, cr = false;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(cl) calc(l - 1);
            if(cr) calc(r);
            if(l & 1) apply(l++, v), cl = true;
            if(r & 1) apply(--r, v), cr = true;
        }
        for(--l; r; l /= 2, r /= 2) {
            if(cl) calc(l);
            if(cr) calc(r);
        }
    }
    void update(ll ind, U v) {
        update(ind, ind + 1, v);
    }
    T query(ll l, ll r) { // range query [l, r)
        push(l), push(r - 1);
        T resl = idT, resr = idT;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) resl = f(resl, t[l++]);
            if(r & 1) resr = f(t[--r], resr);
        }
        return f(resl, resr);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, k;
    cin >> n >> k;
    vm A(n), B(n);
    for(int i = 0; i < n; i++) cin >> A[i] >> B[i];
    vm P(n);
    for(int i = 0; i < n; i++) P[i] = A[i] / B[i];
    
    // multiply modify, sum query
    // function<mint(mint, mint)> fmodify = [](const mint src, const mint val) -> mint{
    //     return src * val;
    // };
    // function<mint(mint, mint, int)> fmodifyk = [](const mint src, const mint val, const int k) -> mint{
    //     return src * val;
    // };
    // function<mint(mint, mint)> fcombine = [](const mint a, const mint b) -> mint{
    //     return a + b;
    // };
    // SegtreeLazy<mint> dp(n + 1, 1, 0, 1, fmodify, fmodifyk, fcombine);
    lztree dp(n + 1);
    for(int i = 0; i <= n; i++) {
        dp.set(i, mint(1));
    }

    for(int i = 0; i <= n; i++) cout << "i : " << i << " dp[i] : " << dp.get(i) << '\n';

    mint ans = 0;
    for(int i = 0; i <= n; i++) {
        mint cval = 1;
        if(i > 0) {
            int L = max(0, i - k);
            cval = dp.query(L, i) * (mint(1) - P[i - 1]);
            cout << "DP : " << i << " " << cval << "\n";
            dp.update(i, cval);
            dp.update(0, i, P[i - 1]);
        }

        // assume next K contiguous starts here
        if(i + k <= n) {
            for(int j = 0; j < k; j++) {
                cval *= P[i + j];
            }
            ans += cval;
            cout << "SEQ : " << i << " " << cval << "\n";
        }
    }
    cout << ans << "\n";
    
    return 0;
}