// /* range updates, single element query. 
// possible with a modified segment tree I hope.
// TODO in platinum - lazy propagation
// */

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// struct Tree {
//     typedef ll T; //update the data type, currently int. often update to ll
//     static constexpr T base = 0;
//     T f(T a, T b) {
//         return a + b; //update this function for different types of queries, currently sum
//     }
//     vector<T> s; int n;
//     Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
//     void set(int pos, T val) {
//         s[pos + n] = val;
//     }
//     void update(int l, int r, T u) { //increases values in [l,r) by u
//         for(l += n, r += n; l < r; l /= 2, r /= 2) {
//             if(l & 1) {
//                 s[l] = f(s[l],u);
//                 l++;
//             }
//             if(r & 1) {
//                 r--;
//                 s[r] = f(s[r],u);
//             }
//         }
//     }
//     T query(int pos) { //queries the value of element at pos
//         T ans = s[pos += n];
//         while(pos /= 2) {
//             ans = f(ans,s[pos]);
//         }
//         return ans;
//     }
// };

// std::ostream& operator<<(std::ostream& os, const Tree &t) {
//     for(auto x : t.s) os << x << " ";
//     return os;
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, q; cin >> n >> q;
//     Tree tree(n);
//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         tree.set(i,num);
//     }
//     for(int i = 0; i < q; i++) {
//         int type; cin >> type;
//         if(type == 1) {
//             ll l, r, u; cin >> l >> r >> u;
//             l--;
//             tree.update(l,r,u);
//         } else {
//             int x; cin >> x;
//             x--;
//             cout << tree.query(x) << "\n";
//         }
//     }

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = 0; //stores the starting values at all nodes, 
    static constexpr D ln = 0;
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //base, count of how many polynomials start at one at the beginning of this node
    int n, size;

    //if OJ is not up to date, remove all occurrences of ln
    Lazy(int n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
    }
    bool isLeaf(int node) {
        return node >= size;
    }
    T query_comb(T val1, T val2) {//update this depending on query type
        return val1 + val2;
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] += val;
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node] += lazy[node];
    }
    void push_lazy(int node, int size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
        }
        lazy[node] = ln;
    }
    void update(int l, int r, D val) {
        _update(1,0,size,l,r, val);
    }
    void _update(int node, int currl, int currr, int &targetl, int &targetr, D val) {
        push_lazy(node, currr - currl);
        if (currl >= targetr || currr <= targetl) return;
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
    T query(int l, int r) {
        return _query(1,0,size,l,r);
    }
    T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr)return qn; 
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
    Lazy<ll,ll> lazy(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        lazy.update(i,i+1,num);
    }
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int a, b, u; cin >> a >> b >> u;
            lazy.update(a-1,b,u);
        }
        if(type == 2) {
            int k; cin >> k;
            cout << lazy.query(k-1,k) << '\n';
        }
    }

    return 0;
}