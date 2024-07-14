#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//lazy segtree is not my friend for this problem :( --> read editorial for solution that runs in time

void solve() {

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    int q; cin >> q;
    
    int iteration = 0;
    map<ll,ll> m;
    vector<array<ll,3>> queries(q);
    for(int i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
        queries[i][0]--;

        m[queries[i][0]] += queries[i][2];
        m[queries[i][1]] -= queries[i][2];
        
        while(m.size() && (*m.begin()).second == 0) {
            m.erase(m.begin());
        }

        if(m.size() && (*m.begin()).second < 0) {
            m.clear();
            iteration = i + 1;
        }
    }

    // cout << "iteration : " << iteration << endl;

    vector<ll> p(n+1);
    
    for(int i = 0; i < iteration; i++) {
        p[queries[i][0]] += queries[i][2];
        p[queries[i][1]] -= queries[i][2];
    }
    
    ll d = 0;
    for(int i = 0; i < n; i++) {
        d += p[i];
        cout << d + a[i] << " \n"[i == n - 1];
    }
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;
// const ll INF = 1e18;
// const ll maxdiff = 5e14;

// template<typename T, typename D>
// struct Lazy {
//     static constexpr T qn = INF; // query neutral, when we query, doing the operation with this value won't change our query
//     static constexpr D ln = 0; //lazy neutral, applying this value to its node will not change its value
//     vector<T> v;      //stores values at each index we are querying for
//     vector<D> lazy;   //stores lazy update values
//     int n, size;
//     //if OJ is not up to date, remove all occurrences of ln
//     Lazy(int n = 0, T def = qn) {
//         this->n = n;
//         this->size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//         lazy.assign(size * 2, ln);
//     }
//     bool isLeaf(int node) {return node >= size;}
//     T query_comb(T val1, T val2) {//update this depending on query type. Sometimes known as pull
//         return min(val1, val2);
//     }
//     //how we combine lazy updates to lazy
//     void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
//         lazy[node] += val;
//     }
//     void main_comb(int node) {//update this depending on query type, how does the lazy value affect value at v for the query?
//         v[node] = min(INF, v[node] + lazy[node]);
//     }
//     void push_lazy(int node) {
//         main_comb(node); //push lazy change to current node
//         if(!isLeaf(node)) {
//             lazy_comb(node * 2, lazy[node]);
//             lazy_comb(node * 2 + 1, lazy[node]);
//         }
//         lazy[node] = ln;
//     }
//     void update(int l, int r, D val) { //[l,r)
//         _update(1,0,size,l,r, val);
//     }
//     void _update(int node, int currl, int currr, int &targetl, int &targetr, D val) {
//         if (currl >= targetr || currr <= targetl) return;
//         push_lazy(node);
//         if(currl >= targetl && currr <= targetr) { //complete overlap
//             lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
//         } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
//             int mid = (currl + currr) / 2;
//             _update(node * 2, currl, mid, targetl, targetr, val);
//             _update(node * 2 + 1, mid, currr, targetl, targetr, val);
//             push_lazy(node * 2);
//             push_lazy(node * 2 + 1);
//             v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
//         }
//     }
//     T query(int l, int r) { // [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
//         if(currr <= targetl || currl >= targetr) return qn; 
//         push_lazy(node); //make pushes necessary before getting value, we always check for 2 cases
//         if(currl >= targetl && currr <= targetr) { //complete overlap
//             return v[node];
//         } else {
//             int mid = (currl + currr) / 2;
//             return query_comb(
//                 _query(node * 2, currl, mid, targetl, targetr),
//                 _query(node * 2 + 1, mid, currr, targetl, targetr)
//             );
//         }
//     }

//     void purge() {
//         ll loval = query(0,n);
//         _purge(1,loval);
//     }

//     void _purge(int node, ll &loval) {
//         cout << "node : " << node << '\n';
//         push_lazy(node);
//         if(isLeaf(node)) {
//             if(v[node] > loval && v[node] <= maxdiff) {
//                 v[node] = INF;
//                 cout << "node : " << node << " is purged\n";
//             }
//         } else {
//             cout << "vnode : " << v[node] << " loval : " << loval << '\n';
//             if(v[node] > loval && v[node] <= maxdiff) {
//                 _purge(node * 2, loval);
//                 _purge(node * 2 + 1, loval);
//                 push_lazy(node * 2);
//                 push_lazy(node * 2 + 1);
//                 v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
//             }
//         }
//     }
// };

// void solve() {
    
//     int n; cin >> n;
//     vector<ll> a(n);
//     for(ll &x : a) cin >> x;
    
//     int q; cin >> q;
//     vector<vector<array<ll,2>>> events(n+1);
//     vector<array<ll,3>> upds(q);
//     for(int i = 1; i <= q; i++) { //i is the time
//         ll l, r, x; cin >> l >> r >> x;
//         events[l-1].push_back({i,x});
//         events[r].push_back({i,-x});
//         upds[i-1] = {l,r,x};
//     }
    
//     Lazy<ll,ll> lazy(q + 1,0LL);
//     for(int i = 0; i < n; i++) {
        
//         for(array<ll,2> event : events[i]) {
//             lazy.update(event[0], q + 1, event[1]);
//         }
//         lazy.purge();
//     }
    
//     int j = -1;
//     // cout << "lazy : ";
//     for(int i = 0; i <= q; i++) {
//         cout << lazy.query(i,i+1) << " ";
//         if(lazy.query(i,i+1) <= maxdiff) {
//             // cout << "j found : " << i << '\n';
//             j = i;
//         }
//     }
    
//     // cout << '\n';

    
//     // cout << "final j : " << j << '\n';
    
//     vector<ll> p(n+1);
    
//     for(int i = 0; i < j; i++) {
//         p[upds[i][0] - 1] += upds[i][2];
//         p[upds[i][1]] -= upds[i][2];
//     }
    
//     ll d = 0;
//     for(int i = 0; i < n; i++) {
//         d += p[i];
//         cout << d + a[i] << " \n"[i == n - 1];
//     }
    
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }