#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll inf = 1e9;

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = inf * inf; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = 0; //lazy neutral, applying this value to its node will not change its value
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //stores lazy update values
    ll n, size;
    //if OJ is not up to date, remove all occurrences of ln
    Lazy(ll n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
    }
    bool isLeaf(ll node) {return node >= size;}
    T query_comb(T val1, T val2) {//update this depending on query type
        return min(val1, val2);
    }
    //how we combine lazy updates to lazy
    void lazy_comb(ll node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] += val;
    }
    void main_comb(ll node, ll size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node] += lazy[node];
    }
    void push_lazy(ll node, ll size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
        }
        lazy[node] = ln;
    }
    void update(ll l, ll r, D val) { //[l,r)
        _update(1,0,size,l,r, val);
    }
    void _update(ll node, ll currl, ll currr, ll &targetl, ll &targetr, D val) {
        if (currl >= targetr || currr <= targetl) return;
        push_lazy(node, currr - currl);
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            ll mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, val);
            push_lazy(node * 2, (currr - currl) / 2);
            push_lazy(node * 2 + 1, (currr - currl) / 2);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(ll l, ll r) { // [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(ll node, ll currl, ll currr, ll &targetl, ll &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr) return qn; 
        push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
        if(currl >= targetl && currr <= targetr) { //complete overlap
            return v[node];
        } else {
            ll mid = (currl + currr) / 2;
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

    ll n, l, k; cin >> n >> l >> k;
    l--; k--;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    set<ll> b(a.begin(), a.end());
    map<ll,ll> m;
    ll i = 0;
    for(ll x : b) {
        m[x] = i++;
    }
    for(ll &x : a) x = m[x];

    vector<Lazy<ll,ll>> dp(k + 1, Lazy<ll,ll>(b.size(), inf));
    dp[0].update(a[l],a[l]+1,-inf);

    for(int i = l + 1; i < n; i++) {
        int h = a[i];
        for(int j = 1; j <= k; j++) {
            ll nx = min({inf,dp[j-1].query(0,h),dp[j].query(h,h+1)});
            // cout << "i : " << i << " j : " << j << " nx : " << nx << '\n';
            dp[j].update(h,h+1,nx-dp[j].query(h,h+1));
            // cout << "after check : " << dp[j].query(h,h+1) << '\n';
        }
        for(int j = 0; j <= k; j++) {
            dp[j].update(0,h,1);
        }
    }

    ll res = dp[k].query(0,b.size());

    for(int i = 0; i < l; i++) if(a[i] >= a[l]) res++;

    cout << (res >= inf ? -1 : res) << '\n';

    return 0;
}