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

template <typename T>
struct SegtreeLazy {
    public:
        int n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        bool* upd;  //marks whether or not a lazy change is here
        T uneut, qneut;

        //single element modify
        function<T(T, T)> fmodify;

        //k element modify
        function<T(T, T, int)> fmodifyk;

        //product of two elements for query
        function<T(T, T)> fcombine;

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
            n = maxSize;
            uneut = updateNeutral;
            qneut = queryNeutral;

            this -> fmodify = fmodify;
            this -> fmodifyk = fmodifyk;
            this -> fcombine = fcombine;

            //raise n to nearest pow 2
            int x = 1;
            while(x < n) {
                x <<= 1;
            }
            n = x;

            t = new T[n * 2];
            d = new T[n * 2];
            upd = new bool[n * 2];

            //make sure to initialize values
            for(int i = 0; i < n; i++){
                t[i + n] = initVal;
            }
            build();
        }

        void assign(vector<T>& arr) {
            for(int i = 0; i < min(n, (int) arr.size()); i++){
                t[i + n] = arr[i];
            }
            build();
        }

        //build tree after manually assigning values
        void build() {
            for(int i = n - 1; i > 0; i--){
                t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
            }
            for(int i = 0; i < n * 2; i++){
                d[i] = uneut;
                upd[i] = false;
            }
        }

        void modify(int l, int r, T val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        void modify(int ind, T val) { //modifies the range [ind, ind + 1)
            _modify(ind, ind + 1, val, 0, n, 1);
        }

        T query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

        T query(int ind) {    //queries the range [ind, ind + 1)
            return _query(ind, ind + 1, 0, n, 1);
        }

    private:
        //calculates value of node based off of children
        //k is the amount of values that this node represents. 
        void combine(int ind, int k) {
            if(ind >= n){
                return;
            }
            int l = ind * 2;
            int r = ind * 2 + 1;
            //make sure children are correct value before calculating
            push(l, k / 2);
            push(r, k / 2);
            t[ind] = fcombine(t[l], t[r]);
        }

        //registers a lazy change llo this node
        void apply(int ind, T val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }

        //applies lazy change to this node
        //k is the amount of values that this node represents. 
        void push(int ind, int k) {
            if(!upd[ind]) {
                return;
            }
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                int l = ind * 2;
                int r = ind * 2 + 1;
                apply(l, d[ind]);
                apply(r, d[ind]);
            }
            upd[ind] = false;
            d[ind] = uneut;
        }

        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr) {
                apply(ind, val);
                push(ind, tr - tl);
                return;
            }
            int mid = tl + (tr - tl) / 2;
            if(l < mid) {
                _modify(l, min(r, mid), val, tl, mid, ind * 2);
            }
            if(r > mid) {
                _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
            }
            combine(ind, tr - tl);
        }

        T _query(int l, int r, int tl, int tr, int ind) {
            if(l == r){
                return qneut;
            }  
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr){
                return t[ind];
            }
            int mid = tl + (tr - tl) / 2;
            T lans = qneut;
            T rans = qneut;
            if(l < mid) {
                lans = _query(l, min(r, mid), tl, mid, ind * 2);
            }
            if(r > mid) {
                rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            }
            return fcombine(lans, rans);
        }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    //coordinate compression
    ll q, w;
    cin >> q >> w;
    vector<pll> a(q);
    for(int i = 0; i < q; i++){
        ll x, y;
        cin >> x >> y;
        ll l = max(0ll, x - y);
        ll r = min(w, x + y);
        a[i] = {l, r};
        // cout << "LR : " << l << " " << r << endl;
    }
    map<ll, int> cm;
    {
        set<ll> s;
        s.insert(0);
        s.insert(w);
        for(int i = 0; i < a.size(); i++){
            s.insert(a[i].first);
            s.insert(a[i].second);
        }
        int ptr = 0;
        for(auto i = s.begin(); i != s.end(); i++){
            cm[*i] = ptr ++;
        }
        // for(auto i = cm.begin(); i != cm.end(); i++){
        //     cout << "CM : " << i->first << " " << i -> second << endl;
        // }
    }
    //init segtree
    function<pll(pll, pll)> fmodify = [](const pll src, const pll val) -> pll{
        return {src.first + val.first, src.second};
    };
    function<pll(pll, pll, int)> fmodifyk = [](const pll src, const pll val, const int k) -> pll{
        return {src.first + val.first, src.second};
    };
    function<pll(pll, pll)> fcombine = [](const pll a, const pll b) -> pll{
        if(a.first < b.first) {
            return a;
        }
        else if(b.first < a.first){
            return b;
        }
        else{
            return {a.first, a.second + b.second};
        }
    };
    SegtreeLazy<pll> segt(cm.size() - 1, {0, 0}, {1e18, 0}, {0, 1}, fmodify, fmodifyk, fcombine);
    {
        vector<pll> sinit(cm.size() - 1);
        vector<ll> cma(0);
        for(auto i = cm.begin(); i != cm.end(); i++){
            cma.push_back(i->first);
        }
        for(int i = 0; i < cm.size() - 1; i++){
            sinit[i] = {0, cma[i + 1] - cma[i]};
            // cout << "SINIT : " << sinit[i].first << " " << sinit[i].second << endl;
        }
        segt.assign(sinit);
    }
    ld s2 = sqrt((ld) 2.0);
    set<pii> ss;
    for(int i = 0; i < q; i++){
        int l = cm[a[i].first];
        int r = cm[a[i].second];
        // cout << "QLR : " << l << " " << r << endl;
        if(ss.count({l, r})){
            ss.erase({l, r});
            segt.modify(l, r, {-1, 0});
        }
        else {
            ss.insert({l, r});
            segt.modify(l, r, {1, 0});
        }
        // cout << "DONE MODIFY" << endl;
        // cout << "QUERY : " << 0 << " " << cm.size() << endl;
        pll qans = segt.query(0, cm.size() - 1);
        // cout << "QANS : " << qans.first << " " << qans.second << endl;
        ld ans = w;
        if(qans.first == 0){
            ans -= qans.second;
        }
        ans *= s2;
        cout << fixed << setprecision(10) << ans << "\n";
    }
    
    return 0;
}