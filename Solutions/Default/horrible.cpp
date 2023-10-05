//https://www.spoj.com/problems/HORRIBLE/
//tested andrew's lazy segment tree and going to optimize it a bit
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

/*
famous words from master Andwerp
lets say that we have a range that is k values in length
the range sum, however we defined sum, is initially equal to src
fmodifyk just returns the new sum, after adding, however we defined add, val to all k elements in the range
in the examples, return src + val is fine for querying the min or max because min and max don't care about how many elements are changed
but querying the sum on the range does care.
also, if we were to define sum as the xor sum, then fmodifyk would be return src ^ (val * (k % 2))
*/

template <typename T>
struct SegtreeLazy {
    public:
        T n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        T uneut, qneut;

        //single element modify
        function<T(T, T)> modifyElement;

        //k element modify
        function<T(T, T, T)> modifyRange;

        //product of two elements for query
        function<T(T, T)> queryType;

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, function<T(T, T)> modifyElement, function<T(T, T, T)> modifyRange, function<T(T, T)> queryType) {
            n = maxSize;
            uneut = updateNeutral;
            qneut = queryNeutral;

            this -> modifyElement = modifyElement;
            this -> modifyRange = modifyRange;
            this -> queryType = queryType;

            //raise n to nearest pow 2
            int x = 1;
            while(x < n) {
                x <<= 1;
            }
            n = x;

            t = new T[n * 2];
            d = new T[n * 2];

            //make sure to initialize values
            for(T i = 0; i < n * 2; i++){
                t[i] = uneut;
            }
            for(T i = 0; i < n * 2; i++){
                d[i] = uneut;
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
        void combine(int ind, T k) {
            if(ind >= n){
                return;
            }
            int l = ind * 2;
            int r = ind * 2 + 1;
            //make sure children are correct value before calculating
            push(l, k / 2);
            push(r, k / 2);
            t[ind] = queryType(t[l], t[r]);
        }

        //registers a lazy change llo this node
        void apply(int ind, T val) {
            d[ind] = modifyElement(d[ind], val);
        }

        //applies lazy change to this node
        //k is the amount of values that this node represents. 
        void push(int ind, T k) {
            if(d[ind] == uneut) {
                return;
            }
            t[ind] = modifyRange(t[ind], d[ind], k);
            if(ind < n) {
                int l = ind * 2;
                int r = ind * 2 + 1;
                apply(l, d[ind]);
                apply(r, d[ind]);
            }
            d[ind] = uneut;
        }

        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(d[ind] != uneut) {
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

        T _query(int l, int r, int tl, int tr, T ind) {
            if(l == r){
                return qneut;
            }  
            if(d[ind] != uneut) {
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
            return queryType(lans, rans);
        }
};

void solve() {
    
    // ll n = 100;

    // -- ASSIGNMENT MODIFY, SUM QUERY --
    // {
    //     function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return val;};
    //     function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll k) -> ll{return val * k;};
    //     function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return a + b;};
    //     run_segt_tests(n, 0, 0, modifyElement, modifyRange, queryType);
    // }

    ll n, q; cin >> n >> q;



        function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return src + val;};
        function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll k) -> ll{return src + val;};
        function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return min(a, b);};
        SegtreeLazy<ll> tree(n, 0, 0, modifyElement, modifyRange, queryType);


    for(ll i = 0; i < q; i++) {
        ll type; cin >> type;
        if(type == 0) {
            ll l, r, v; cin >> l >> r >> v;
            tree.modify(l-1,r,v);
        } else {
            int l, r; cin >> l >> r;
            cout << tree.query(l-1,r) << "\n";
        }
    }

    // -- INCREMENT MODIFY, MINIMUM QUERY --
    // {
    //     function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return src + val;};
    //     function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll k) -> ll{return src + val;};
    //     function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return min(a, b);};
    //     run_segt_tests(n, 0, 1e9, modifyElement, modifyRange, queryType);
    // }

    // -- ASSIGNMENT MODIFY, MINIMUM QUERY --
    // {
    //     function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return val;};
    //     function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll k) -> ll{return val;};
    //     function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return min(a, b);};
    //     run_segt_tests(n, 0, 1e9, modifyElement, modifyRange, queryType);
    // }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}