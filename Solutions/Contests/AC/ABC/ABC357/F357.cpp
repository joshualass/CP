#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*

problem that can solved with a single lazy seg tree once you can see how
originally tried square root decomposition, but segtree uses similar idea. 

lazy    0 - insignificant
        1 - difference in a
        2 - difference in b

q       0 - sum of all a*b
        1 - sum of a
        2 - sum of b
*/

std::ostream& operator<<(std::ostream& os, const array<ll,3> a) {
    for(auto x : a) os << x << " ";
    return os;
}

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
struct Lazy {
    static constexpr T qn = {0,0,0}; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = {0,0,0}; //lazy neutral, applying this value to its node will not change its value
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
        array<ll,3> res = {(val1[0] + val2[0]) % MOD, (val1[1] + val2[1]) % MOD, (val1[2] + val2[2]) % MOD};
        // cout << "query comb val1 : " << val1 << " val2 : " << val2 << " res : " << res << '\n';
        return res;
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node][1] = (lazy[node][1] + val[1]) % MOD;
        lazy[node][2] = (lazy[node][2] + val[2]) % MOD;
    }
    void main_comb(int node, ll size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node][0] = (v[node][0] + lazy[node][1] % MOD * v[node][2]) % MOD;
        v[node][1] = (v[node][1] + lazy[node][1] * size) % MOD;
        v[node][0] = (v[node][0] + lazy[node][2] % MOD * v[node][1]) % MOD;
        v[node][2] = (v[node][2] + lazy[node][2] * size) % MOD;
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
    
    int n, q; cin >> n >> q;
    Lazy<array<ll,3>, array<ll,3>> lazy(n);

    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        lazy.update(i,i+1,{0,a,0});
    }

    for(int i = 0; i < n; i++) {
        ll b; cin >> b;
        lazy.update(i,i+1,{0,0,b});
    }

    // cout << "v\n" << lazy.v << '\n';
    // cout << "lazy\n" << lazy.lazy << '\n';

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll l, r, x; cin >> l >> r >> x;
            l--;
            lazy.update(l,r,{0,x,0});
        } else if(type == 2) {
            ll l, r, x; cin >> l >> r >> x;
            l--;
            lazy.update(l,r,{0,0,x});
        } else {
            ll l, r; cin >> l >> r;
            l--;
            cout << lazy.query(l,r)[0] << '\n';
        }
        // cout << "updated lazy tree /!\\\n";
        // cout << "v\n" << lazy.v << '\n';
        // cout << "lazy\n" << lazy.lazy << '\n';  
    }

    return 0;
}

//square root decomposition also works, but let's practice lazy seg tree
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;
// const int MAXN = 2e5;
// const int sqn = 447;

// ll blockprods[sqn+1];
// ll blockasums[sqn+1];
// ll blockbsums[sqn+1];
// ll blockadiffs[sqn+1];
// ll blockbdiffs[sqn+1];

// ll a[MAXN];
// ll b[MAXN];

// int getblock(int b) {
//     return b / sqn;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     memset(blockprods, 0, sizeof(blockprods));
//     memset(blockasums, 0, sizeof(blockasums));
//     memset(blockbsums, 0, sizeof(blockbsums));
//     memset(blockadiffs, 0, sizeof(blockadiffs));
//     memset(blockbdiffs, 0, sizeof(blockbdiffs));

//     memset(a, 0, sizeof(a));
//     memset(b, 0, sizeof(b));
    
//     int n, q; cin >> n >> q;
//     for(int i = 0; i < n; i++) cin >> a[i];
//     for(int i = 0; i < n; i++) cin >> b[i];

//     for(int i = 0; i < n; i++) {
//         blockasums[getblock(i)] += a[i];
//         blockasums[getblock(i)] %= MOD;
//         blockbsums[getblock(i)] += b[i];
//         blockbsums[getblock(i)] %= MOD;
//         blockprods[getblock(i)] += a[i] * b[i];
//         blockprods[getblock(i)] %= MOD;
//     }

//     for(int i = 0; i < q; i++) {
//         int type; cin >> type;
//         if(type == 1) {
//             ll l, r, x; cin >> l >> r >> x;
//             l--; r--;
//             while(l <= r && l % sqn != 0) { //increase l until it is at the beginning of a block or it passes r
//                 int block = getblock(l);
//                 //remove current product
//                 blockprods[block] -= (a[l] + blockasums[block]) * (b[l] * blockbsums[block]) % MOD;
//                 if(blockprods[block] < 0) blockprods[block] += MOD;
//                 //update a stuff
//                 a[l] += x;
//                 a[l] %= MOD;
//                 blockasums[block] += x;
//                 blockasums[block] %= MOD;
//                 //update current product
//                 blockprods[block] += (a[l] + blockasums[block]) * (b[l] * blockbsums[block]) % MOD;
//                 blockprods[block] %= MOD;
//                 l++;
//             }
//         }
//     }

//     return 0;
// }